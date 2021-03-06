// Copyright (c) 2021 Use Your Imagination

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
#include "Modules/Base/PersonalModules/BasePersonalModule.h"
#include "Modules/Base/WeaponModules/BaseWeaponModule.h"
#include "Interfaces/Modules/Descriptions/PlatinumModule.h"

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

	if (Cast<AAmmo>(OtherActor) || Cast<UBaseWeapon>(OtherActor) || Cast<UCapsuleComponent>(OtherComp))
	{
		return;
	}

	bool isActorValid = IsValid(OtherActor);
	bool shotThrough = isActorValid && OtherActor->Implements<UShotThrough>();
	bool destroyAmmo = false;
	auto decreaseDamage = [this](float percentDamageReduction, float flatDamageReduction)
	{
		ailmentInflictorUtility->appendMoreDamageCoefficient(-Utility::fromPercent(percentDamageReduction));

		ailmentInflictorUtility->setAdditionalDamage(ailmentInflictorUtility->getAdditionalDamage() - flatDamageReduction);
	};

	if (isActorValid && lastTarget == OtherActor)
	{
		return;
	}

	if (shotThrough)
	{
		IShotThrough::Execute_impactAction(OtherActor, this, SweepResult);

		lastTarget = OtherActor;

		decreaseDamage(IShotThrough::Execute_getPercentageDamageReduction(OtherActor), IShotThrough::Execute_getFlatDamageReduction(OtherActor));

		if (ailmentInflictorUtility->calculateTotalDamage() > 0.0f)
		{
			TObjectPtr<UNiagaraComponent> onHit = UNiagaraFunctionLibrary::SpawnSystemAtLocation
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
	else if (SweepResult.PhysMaterial.IsValid() && UPhysicalMaterial::DetermineSurfaceType(SweepResult.PhysMaterial.Get()) != EPhysicalSurface::SurfaceType_Default)
	{
		const FShootThroughSurface& surface = ULostConnectionAssetManager::get().getDefaults()[SweepResult.PhysMaterial];

		if (surface.percentDamageReduction == -1.0f)
		{
			destroyAmmo = true;
		}
		else
		{
			decreaseDamage(surface.percentDamageReduction, surface.flatDamageReducation);
		}
	}

	if (destroyAmmo || ailmentInflictorUtility->calculateTotalDamage() <= 0.0f)
	{
		mesh->SetVisibility(true);

		mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		mesh->SetSimulatePhysics(true);

		mesh->SetStaticMesh(brokenAmmoMeshAsset);

		movement->ProjectileGravityScale = 1.0f;

		movement->Velocity = FVector(0.0f);

		visibleMesh->SetVisibility(false);

		tracer->Deactivate();

		TObjectPtr<UNiagaraComponent> onHit = UNiagaraFunctionLibrary::SpawnSystemAtLocation
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

void AAmmo::copyProperties(TObjectPtr<UBaseWeapon> weapon)
{
	ailmentInflictorUtility->setBaseDamage(weapon->getBaseDamage());

	ailmentInflictorUtility->setAddedDamage(weapon->getAddedDamage());

	ailmentInflictorUtility->setAdditionalDamage(weapon->getAdditionalDamage());

	ailmentInflictorUtility->damageType = weapon->getDamageType();

	ailmentInflictorUtility->setBaseCrushingHitChance(weapon->getBaseCrushingHitChance());

	ailmentInflictorUtility->setAdditionalCrushingHitChance(weapon->getAdditionalCrushingHitChance());

	owner = weapon->getOwner();

	if (owner.IsValid())
	{
		if (IPersonalModulesHolder* holder = Cast<IPersonalModulesHolder>(owner))
		{
			Utility::applyDamageModules(this, holder->getPersonalEquippedModules(), ailmentInflictorUtility);

			Utility::applyDamageModules(this, holder->getActivePersonalModules(), ailmentInflictorUtility);
		}

		if (IWeaponModulesHolder* holder = Cast<IWeaponModulesHolder>(owner))
		{
			Utility::applyDamageModules(this, holder->getWeaponModules(), ailmentInflictorUtility);

			Utility::applyDamageModules(this, holder->getActiveWeaponModules(), ailmentInflictorUtility);
		}
	}
}

TObjectPtr<UStaticMeshComponent> AAmmo::getAmmoMeshComponent() const
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
