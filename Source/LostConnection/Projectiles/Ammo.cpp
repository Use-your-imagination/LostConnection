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
#include "Interfaces/Modules/Holders/PersonalModulesHolder.h"
#include "Interfaces/Modules/Holders/WeaponModulesHolder.h"
#include "Interfaces/Modules/Damage/DamageModule.h"
#include "Interfaces/Modules/Damage/WeaponDamageModule.h"
#include "Modules/BasePersonalModule.h"
#include "Modules/BaseWeaponModule.h"

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

		ailmentInflictorUtility->setBaseDamage
		(
			ailmentInflictorUtility->getBaseDamage() *
			(1.0f - Utility::fromPercent(IShotThrough::Execute_getPercentageDamageReduction(OtherActor))) - IShotThrough::Execute_getFlatDamageReduction(OtherActor)
		);

		if (ailmentInflictorUtility->getBaseDamage() > 0.0f)
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
		ailmentInflictorUtility->setBaseDamage(0.0f);
	}

	if (ailmentInflictorUtility->getBaseDamage() <= 0.0f)
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

template<typename ImplementsModuleInterface, typename ModuleInterface, typename ModuleT>
void AAmmo::applyModules(const TArray<ModuleT*>& modules)
{
	for (const auto& module : modules)
	{
		if (module->Implements<ImplementsModuleInterface>())
		{
			const ModuleInterface* damageModule = Cast<const ModuleInterface>(module);

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

	ailmentInflictorUtility = CreateDefaultSubobject<UAilmentInflictorUtility>("AilmentInflictorUtility");

	SetRootComponent(mesh);

	mesh->SetGenerateOverlapEvents(true);

	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	mesh->bReturnMaterialOnMove = true;

	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::onBeginOverlap);

	mesh->SetVisibility(false);

	visibleMesh->SetupAttachment(mesh);

	visibleMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	visibleMesh->SetIsReplicated(true);

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

	mesh->AddRelativeRotation(spread);

	visibleMesh->SetRelativeTransform(visibleAmmoRelativeTransform);

	visibleMesh->AddRelativeRotation({ 0.0f, 270.0f ,0.0f });

	FinishSpawning({}, true);
}

void AAmmo::copyProperties(UBaseWeapon* weapon)
{
	// damage = weapon->getBaseDamage();
	// 
	// addedDamage = weapon->getAddedDamage();
	// 
	// additionalDamage = weapon->getAdditionalDamage();
	// 
	// damageType = weapon->getDamageType();
	// 
	// crushingHitChance = weapon->getBaseCrushingHitChance();
	// 
	// additionalCrushingHitChance = weapon->getAdditionalCrushingHitChance();

	owner = weapon->getOwner();

	if (owner.IsValid())
	{
		if (owner->Implements<UPersonalModulesHolder>())
		{
			this->applyModules<UDamageModule, IDamageModule>(Cast<IPersonalModulesHolder>(owner)->getPersonalEquippedModules());

			this->applyModules<UDamageModule, IDamageModule>(Cast<IPersonalModulesHolder>(owner)->getPersonalUnequippedModules());
		}

		if (owner->Implements<UWeaponModulesHolder>())
		{
			this->applyModules<UWeaponDamageModule, IWeaponDamageModule>(Cast<IWeaponModulesHolder>(owner)->getWeaponModules());	
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

UAilmentInflictorUtility* AAmmo::getAilmentInflictorUtility() const
{
	return ailmentInflictorUtility;
}
