// Copyright (c) 2021 Use-your-imagination

#include "BaseAmmo.h"

#include "UObject/ConstructorHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Weapons/BaseWeapon.h"
#include "FakeAmmo.h"
#include "Characters/BaseDrone.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Utility/Utility.h"
#include "Constants/Constants.h"
#include "Interfaces/Gameplay/Modules/MainModules/DamageModule.h"
#include "Interfaces/Gameplay/Modules/WeaponModules/WeaponDamageModule.h"

#pragma warning(disable: 4458)

void ABaseAmmo::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	mesh->SetStaticMesh(meshAsset);

	movement->InitialSpeed = ammoSpeed;
	movement->MaxSpeed = ammoSpeed;

	fakeAmmoTemplate->getFakeAmmoMeshComponent()->SetStaticMesh(meshAsset);

	fakeAmmoTemplate->getFakeTracerComponent()->SetAsset(tracerAsset);

	fakeAmmoTemplate->setSpeed(ammoSpeed);
}

void ABaseAmmo::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	if (IsPendingKill() || Cast<ABaseAmmo>(OtherActor) || Cast<UBaseWeapon>(OtherActor) || Cast<UCapsuleComponent>(OtherComp))
	{
		return;
	}

	bool shotThrough = OtherActor->Implements<UShotThrough>();

	if (IsValid(OtherActor) && lastTarget == OtherActor)
	{
		return;
	}

	if (shotThrough && IsValid(OtherActor))
	{
		IShotThrough::Execute_impactAction(OtherActor, this, SweepResult);

		lastTarget = OtherActor;

		damage = damage * (1.0f - IShotThrough::Execute_getPercentageDamageReduction(OtherActor) * 0.01f) - IShotThrough::Execute_getFlatDamageReduction(OtherActor);

		if (damage > 0.0f)
		{
			UNiagaraComponent* onHit = UNiagaraFunctionLibrary::SpawnSystemAtLocation
			(
				GetWorld(),
				onHitAsset,
				GetActorLocation(),
				GetActorRotation(),
				FVector::OneVector,
				true,
				true,
				ENCPoolMethod::AutoRelease
			);

			onHit->SetNiagaraVariableBool("DeathState", false);
		}
	}
	else
	{
		damage = 0.0f;
	}

	if (damage <= 0.0f)
	{
		mesh->SetVisibility(true, true);

		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		mesh->SetSimulatePhysics(true);

		mesh->SetStaticMesh(brokenAmmoMeshAsset);

		movement->ProjectileGravityScale = 1.0f;

		movement->Velocity = FVector(0.0f);

		if (IsValid(fakeAmmo))
		{
			fakeAmmo->Destroy();
			
			fakeAmmo = nullptr;
		}

		UNiagaraComponent* onHit = UNiagaraFunctionLibrary::SpawnSystemAtLocation
		(
			GetWorld(),
			onHitAsset,
			GetActorLocation(),
			GetActorRotation(),
			FVector::OneVector,
			true,
			true,
			ENCPoolMethod::AutoRelease
		);

		onHit->SetNiagaraVariableBool("DeathState", true);

		MarkPendingKill();
	}
}

ABaseAmmo::ABaseAmmo() :
	ammoSpeed(UConstants::ammoSpeed)
{
	PrimaryActorTick.bCanEverTick = false;
	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
	bReplicates = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("AmmoMesh");
	movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	fakeAmmoTemplate = CreateDefaultSubobject<AFakeAmmo>("FakeAmmoTemplate");

	SetRootComponent(mesh);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->bReturnMaterialOnMove = true;

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::onBeginOverlap);

	mesh->SetVisibility(false, true);

	movement->SetUpdatedComponent(mesh);

	movement->ProjectileGravityScale = 0.0f;

	movement->SetIsReplicated(true);
}

void ABaseAmmo::launch(const TWeakObjectPtr<ABaseCharacter>& character, const FTransform& fakeAmmoTransform, const FRotator& spread)
{
	if (!character.IsValid())
	{
		return;
	}

	isAlly = character->getIsAlly();

	mesh->AddRelativeRotation(spread);

	UGameplayStatics::FinishSpawningActor(this, GetActorTransform());

	FActorSpawnParameters parameters;

	parameters.bDeferConstruction = true;
	parameters.Template = fakeAmmoTemplate;
	parameters.Owner = this;
	
	fakeAmmo = character->GetWorld()->SpawnActor<AFakeAmmo>(AFakeAmmo::StaticClass(), fakeAmmoTransform, parameters);

	fakeAmmo->getFakeAmmoMeshComponent()->AddRelativeRotation(spread);

	UGameplayStatics::FinishSpawningActor(fakeAmmo, fakeAmmoTransform);
}

void ABaseAmmo::copyProperties(UBaseWeapon* weapon)
{
	damage = weapon->getBaseDamage();

	addedDamage = weapon->getAddedDamage();

	additionalDamage = weapon->getAdditionalDamage();

	damageType = weapon->getDamageType();

	crushingHitChance = weapon->getCrushingHitChance();

	additionalCrushingHitChance = weapon->getAdditionalCrushingHitChance();

	owner = weapon->getOwner();

	if (owner.IsValid())
	{
		if (owner->Implements<UMainModulesHolder>())
		{
			const TArray<UNetworkObject*>& modules = Cast<IMainModulesHolder>(owner.Get())->getMainModules();

			for (const auto& module : modules)
			{
				if (module->Implements<UDamageModule>())
				{
					const IDamageModule* damageModule = Cast<const IDamageModule>(module);

					if (damageModule->getDamageType() != damageType)
					{
						continue;
					}

					addedDamage += damageModule->getAddedDamage();
					increasedDamageCoefficients.Add(damageModule->getIncreasedDamage());
					moreDamageCoefficients.Add(damageModule->getMoreDamage());
					additionalDamage += damageModule->getAdditionalDamage();
				}
			}
		}

		if (owner->Implements<UWeaponModulesHolder>())
		{
			const TArray<UNetworkObject*>& modules = Cast<IWeaponModulesHolder>(owner.Get())->getWeaponModules();

			for (const auto& module : modules)
			{
				if (module->Implements<UWeaponDamageModule>())
				{
					const IWeaponDamageModule* weaponDamageModule = Cast<const IWeaponDamageModule>(module);

					if (weaponDamageModule->getDamageType() != damageType)
					{
						continue;
					}

					addedDamage += weaponDamageModule->getAddedDamage();
					increasedDamageCoefficients.Add(weaponDamageModule->getIncreasedDamage());
					moreDamageCoefficients.Add(weaponDamageModule->getMoreDamage());
					additionalDamage += weaponDamageModule->getAdditionalDamage();
				}
			}
		}
	}
}

UStaticMeshComponent* ABaseAmmo::getAmmoMeshComponent() const
{
	return mesh;
}

bool ABaseAmmo::getIsAlly() const
{
	return isAlly;
}

const TWeakObjectPtr<ABaseCharacter>& ABaseAmmo::getOwner() const
{
	return owner;
}

void ABaseAmmo::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void ABaseAmmo::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void ABaseAmmo::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void ABaseAmmo::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void ABaseAmmo::setBaseDamage(float damage)
{
	damage = damage;
}

void ABaseAmmo::setAddedDamage(float addedDamage)
{
	this->addedDamage = addedDamage;
}

void ABaseAmmo::setAdditionalDamage(float additionalDamage)
{
	this->additionalDamage = additionalDamage;
}

void ABaseAmmo::setCrushingHitChance_Implementation(float newCrushingHitChance)
{
	crushingHitChance = newCrushingHitChance;
}

void ABaseAmmo::setAdditionalCrushingHitChance_Implementation(float newAdditionalCrushingHitChance)
{
	additionalCrushingHitChance = newAdditionalCrushingHitChance;
}

float ABaseAmmo::getBaseDamage() const
{
	return damage;
}

float ABaseAmmo::getAddedDamage() const
{
	return 0.0f;
}

float ABaseAmmo::getAdditionalDamage() const
{
	return additionalDamage;
}

TArray<float> ABaseAmmo::getIncreasedDamageCoefficients() const
{
	return {};
}

TArray<float> ABaseAmmo::getMoreDamageCoefficients() const
{
	return {};
}

typeOfDamage ABaseAmmo::getDamageType() const
{
	return damageType;
}

float ABaseAmmo::getCrushingHitChance() const
{
	return crushingHitChance;
}

float ABaseAmmo::getAdditionalCrushingHitChance() const
{
	return additionalCrushingHitChance;
}
