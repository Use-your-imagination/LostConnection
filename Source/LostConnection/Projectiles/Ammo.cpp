// Copyright (c) 2021 Use-your-imagination

#include "Ammo.h"

#include "UObject/ConstructorHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Weapons/BaseWeapon.h"
#include "Characters/BaseDrone.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Utility/Utility.h"
#include "Constants/Constants.h"
#include "Interfaces/Gameplay/Modules/MainModules/DamageModule.h"
#include "Interfaces/Gameplay/Modules/WeaponModules/WeaponDamageModule.h"

#pragma warning(disable: 4458)

void AAmmo::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	movement->Velocity = mesh->GetForwardVector() * ammoSpeed;
	movement->MaxSpeed = ammoSpeed;
}

void AAmmo::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	if (IsPendingKill() || Cast<AAmmo>(OtherActor) || Cast<UBaseWeapon>(OtherActor) || Cast<UCapsuleComponent>(OtherComp))
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
		mesh->SetVisibility(true);

		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		mesh->SetSimulatePhysics(true);

		mesh->SetStaticMesh(brokenAmmoMeshAsset);

		movement->ProjectileGravityScale = 1.0f;

		movement->Velocity = FVector(0.0f);

		visibleMesh->SetVisibility(false);

		tracer->Deactivate();

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

		Destroy();
	}
}

AAmmo::AAmmo() :
	ammoSpeed(UConstants::ammoSpeed)
{
	PrimaryActorTick.bCanEverTick = false;
	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
	bReplicates = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("AmmoMesh");
	visibleMesh = CreateDefaultSubobject<UStaticMeshComponent>("FakeAmmoMesh");
	tracer = CreateDefaultSubobject<UNiagaraComponent>("Tracer");
	movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	
	SetRootComponent(mesh);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->bReturnMaterialOnMove = true;

	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::onBeginOverlap);

	mesh->SetVisibility(false);

	visibleMesh->SetupAttachment(mesh);

	visibleMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	tracer->SetupAttachment(visibleMesh);

	movement->SetUpdatedComponent(mesh);

	movement->ProjectileGravityScale = 0.0f;

	movement->SetIsReplicated(true);
}

void AAmmo::launch(const TWeakObjectPtr<ABaseCharacter>& character, const FTransform& visibleAmmoRelativeTransform, const FRotator& spread)
{
	if (!character.IsValid())
	{
		return;
	}

	isAlly = character->getIsAlly();

	mesh->AddWorldRotation(spread);

	visibleMesh->SetRelativeTransform(visibleAmmoRelativeTransform);

	visibleMesh->AddRelativeRotation({ 0.0f, 270.0f ,0.0f });

	UGameplayStatics::FinishSpawningActor(this, GetActorTransform());
}

void AAmmo::copyProperties(UBaseWeapon* weapon)
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

UStaticMeshComponent* AAmmo::getAmmoMeshComponent() const
{
	return mesh;
}

bool AAmmo::getIsAlly() const
{
	return isAlly;
}

const TWeakObjectPtr<ABaseCharacter>& AAmmo::getOwner() const
{
	return owner;
}

void AAmmo::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void AAmmo::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void AAmmo::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void AAmmo::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void AAmmo::setBaseDamage(float damage)
{
	damage = damage;
}

void AAmmo::setAddedDamage(float addedDamage)
{
	this->addedDamage = addedDamage;
}

void AAmmo::setAdditionalDamage(float additionalDamage)
{
	this->additionalDamage = additionalDamage;
}

void AAmmo::setCrushingHitChance_Implementation(float newCrushingHitChance)
{
	crushingHitChance = newCrushingHitChance;
}

void AAmmo::setAdditionalCrushingHitChance_Implementation(float newAdditionalCrushingHitChance)
{
	additionalCrushingHitChance = newAdditionalCrushingHitChance;
}

float AAmmo::getBaseDamage() const
{
	return damage;
}

float AAmmo::getAddedDamage() const
{
	return 0.0f;
}

float AAmmo::getAdditionalDamage() const
{
	return additionalDamage;
}

TArray<float> AAmmo::getIncreasedDamageCoefficients() const
{
	return {};
}

TArray<float> AAmmo::getMoreDamageCoefficients() const
{
	return {};
}

typeOfDamage AAmmo::getDamageType() const
{
	return damageType;
}

float AAmmo::getCrushingHitChance() const
{
	return crushingHitChance;
}

float AAmmo::getAdditionalCrushingHitChance() const
{
	return additionalCrushingHitChance;
}
