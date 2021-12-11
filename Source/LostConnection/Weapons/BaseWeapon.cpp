// Copyright (c) 2021 Use-your-imagination

#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Utility/MultiplayerUtility.h"
#include "Engine/LostConnectionPlayerState.h"
#include "Engine/LostConnectionGameState.h"
#include "Characters/BaseDrone.h"
#include "Characters/BaseBot.h"
#include "Constants/Constants.h"

#pragma warning(disable: 4458)

bool UBaseWeapon::IsSupportedForNetworking() const
{
	return true;
}

void UBaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseWeapon, ammoType);

	DOREPLIFETIME(UBaseWeapon, damageType);

	DOREPLIFETIME(UBaseWeapon, damage);

	DOREPLIFETIME(UBaseWeapon, currentMagazineSize);

	DOREPLIFETIME(UBaseWeapon, magazineSize);

	DOREPLIFETIME(UBaseWeapon, ammoCost);

	DOREPLIFETIME(UBaseWeapon, roundsPerSecond);

	DOREPLIFETIME(UBaseWeapon, weaponType);

	DOREPLIFETIME(UBaseWeapon, spreadDistance);

	DOREPLIFETIME(UBaseWeapon, crushingHitChance);

	DOREPLIFETIME(UBaseWeapon, additionalCrushingHitChance);

	DOREPLIFETIME(UBaseWeapon, length);
}

void UBaseWeapon::shoot()
{
	if (owner->getIsReloading())
	{
		return;
	}

	if (weaponType == weaponTypes::semiAutomatic || weaponType == weaponTypes::single)
	{
		MultiplayerUtility::runOnServerReliable(owner.Get(), "resetShoot");
	}
	else if (weaponType == weaponTypes::delay)
	{
		return;
	}

	if (currentMagazineSize >= ammoCost)
	{
		FVector weaponBarrelLocation = owner->getCurrentWeaponMeshComponent()->GetBoneLocation("barrel");
		FTransform ammoTransform;
		FTransform fakeAmmoTransform;
		ABaseDrone* drone = Cast<ABaseDrone>(owner.Get());

		if (drone)
		{
			UCameraComponent* camera = drone->GetFollowCamera();

			ammoTransform = FTransform
			(
				camera->GetForwardVector().ToOrientationRotator(),
				camera->GetComponentLocation() + (drone->GetCameraOffset()->TargetArmLength + length) * camera->GetForwardVector()
			);
			
			fakeAmmoTransform = FTransform
			(
				((ammoTransform.GetLocation() + UConstants::shootDistance * camera->GetForwardVector()) - weaponBarrelLocation).ToOrientationRotator(),
				weaponBarrelLocation
			);
		}
		else
		{
			ABaseBot* bot = Cast<ABaseBot>(owner.Get());
			AAIController* controller = bot->GetController<AAIController>();
			ABaseDrone* target = Cast<ABaseDrone>(controller->GetBlackboardComponent()->GetValueAsObject("Drone"));
			
			if (target && target->IsValidLowLevelFast())
			{
				ammoTransform = FTransform
				(
					(target->GetActorLocation() - bot->GetActorLocation()).ToOrientationRotator(),
					weaponBarrelLocation
				);

				fakeAmmoTransform = ammoTransform;
			}
		}

		ABaseAmmo* launchedAmmo = Utility::getGameState(owner.Get())->spawn<ABaseAmmo>(ammoClass.Get(), ammoTransform);

		launchedAmmo->copyProperties(this);

		float pitch = FMath::RandRange(-spreadDistance, spreadDistance);
		float yaw = FMath::Tan(FMath::Acos(pitch / spreadDistance)) * pitch;

		launchedAmmo->launch(owner.Get(), fakeAmmoTransform, {pitch, FMath::RandRange(-yaw, yaw), 0.0f});

		currentMagazineSize -= ammoCost;

		currentTimeBetweenShots = timeBetweenShots;
	}
	else
	{
		MultiplayerUtility::runOnServerReliableWithMulticast(owner.Get(), "reload");
	}
}

UBaseWeapon::UBaseWeapon() :
	ammoCost(1),
	length(100.0f)
{
	
}

void UBaseWeapon::startShoot()
{
	isShooting = true;
}

void UBaseWeapon::resetShoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
{
	isShooting = false;

	if (weaponType == weaponTypes::delay)
	{
		weaponType = weaponTypes::single;

		this->shoot();

		weaponType = weaponTypes::delay;
	}
}

void UBaseWeapon::alternativeMode()
{

}

void UBaseWeapon::updateTimeBetweenShots_Implementation()
{
	timeBetweenShots = 1.0f / StaticCast<float>(roundsPerSecond);
}

void UBaseWeapon::Tick(float DeltaTime)
{
	if (currentTimeBetweenShots > 0.0f)
	{
		currentTimeBetweenShots -= DeltaTime;

		if (currentTimeBetweenShots < 0.0f)
		{
			currentTimeBetweenShots = 0.0f;
		}
	}

	if (isShooting && !currentTimeBetweenShots)
	{
		this->shoot();
	}
}

void UBaseWeapon::setOwner_Implementation(ABaseCharacter* owner)
{
	this->owner = owner;
}

void UBaseWeapon::setAmmoType_Implementation(ammoTypes newAmmoType)
{
	ammoType = newAmmoType;
}

void UBaseWeapon::setBaseDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UBaseWeapon::setCurrentMagazineSize_Implementation(int32 newCurrentMagazineSize)
{
	currentMagazineSize = newCurrentMagazineSize;
}

void UBaseWeapon::setRateOfFire_Implementation(int32 newRoundsPerSecond)
{
	roundsPerSecond = newRoundsPerSecond;
}

void UBaseWeapon::setWeaponType_Implementation(weaponTypes newWeaponType)
{
	weaponType = newWeaponType;
}

USkeletalMesh* UBaseWeapon::getWeaponMesh() const
{
	return mesh;
}

UStaticMesh* UBaseWeapon::getMagazineMesh() const
{
	return magazineMesh;
}

ammoTypes UBaseWeapon::getAmmoType() const
{
	return ammoType;
}

typeOfDamage UBaseWeapon::getDamageType() const
{
	return damageType;
}

float UBaseWeapon::getBaseDamage() const
{
	return damage;
}

int32 UBaseWeapon::getCurrentMagazineSize() const
{
	return currentMagazineSize;
}

int32 UBaseWeapon::getMagazineSize() const
{
	return magazineSize;
}

int32 UBaseWeapon::getRoundsPerSecond() const
{
	return roundsPerSecond;
}

weaponTypes UBaseWeapon::getWeaponType() const
{
	return weaponType;
}

UClass* UBaseWeapon::getAnimationBlueprint() const
{
	return animationBlueprint.Get();
}

const TWeakObjectPtr<ABaseCharacter>& UBaseWeapon::getOwner() const
{
	return owner;
}

float UBaseWeapon::getCrushingHitChance() const
{
	return crushingHitChance;
}

float UBaseWeapon::getAdditionalCrushingHitChance() const
{
	return additionalCrushingHitChance;
}
