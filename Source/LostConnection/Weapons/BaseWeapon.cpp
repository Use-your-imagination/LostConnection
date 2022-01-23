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

FTransform UBaseWeapon::calculateAmmoTransform(const FTransform& weaponBarrelTransform)
{
	ABaseDrone* drone = Cast<ABaseDrone>(owner);

	if (IsValid(drone))
	{
		UCameraComponent* camera = drone->GetFollowCamera();

		return FTransform
		(
			camera->GetForwardVector().ToOrientationRotator(),
			camera->GetComponentLocation() + camera->GetForwardVector() * (drone->GetCameraOffset()->TargetArmLength + length)
		);
	}
	else
	{
		ABaseBot* bot = Cast<ABaseBot>(owner);
		AAIController* controller = bot->GetController<AAIController>();
		ABaseDrone* target = Cast<ABaseDrone>(controller->GetBlackboardComponent()->GetValueAsObject("Drone"));

		if (IsValid(target))
		{
			return FTransform
			(
				(target->GetActorLocation() - bot->GetActorLocation()).ToOrientationRotator(),
				weaponBarrelTransform.GetLocation()
			);
		}
	}

	return {};
}

FTransform UBaseWeapon::calculateVisibleAmmoTransform(const FTransform& weaponBarrelTransform, const FTransform& ammoTransform)
{
	if (!IsValid(Cast<ABaseDrone>(owner)))
	{
		return {};
	}

	return weaponBarrelTransform.GetRelativeTransform(ammoTransform);
}

void UBaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseWeapon, ammoType);

	DOREPLIFETIME(UBaseWeapon, damageType);

	DOREPLIFETIME(UBaseWeapon, damage);

	DOREPLIFETIME(UBaseWeapon, addedDamage);

	DOREPLIFETIME(UBaseWeapon, additionalDamage);

	DOREPLIFETIME(UBaseWeapon, increasedDamageCoefficients);

	DOREPLIFETIME(UBaseWeapon, moreDamageCoefficients);

	DOREPLIFETIME(UBaseWeapon, currentMagazineSize);

	DOREPLIFETIME(UBaseWeapon, magazineSize);

	DOREPLIFETIME(UBaseWeapon, ammoCost);

	DOREPLIFETIME(UBaseWeapon, roundsPerSecond);

	DOREPLIFETIME(UBaseWeapon, weaponType);

	DOREPLIFETIME(UBaseWeapon, spreadDistance);

	DOREPLIFETIME(UBaseWeapon, crushingHitChance);

	DOREPLIFETIME(UBaseWeapon, additionalCrushingHitChance);

	DOREPLIFETIME(UBaseWeapon, length);

	DOREPLIFETIME(UBaseWeapon, currentAccuracyMultiplier);
}

void UBaseWeapon::shoot()
{
	if (!owner.IsValid() || owner->getIsReloading())
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

	int32 shotsCount = FMath::FloorToInt(FMath::Abs(currentTimeBetweenShots / timeBetweenShots));
	int32 boneIndex = owner->getCurrentWeaponMeshComponent()->GetBoneIndex("barrel");
	FTransform weaponBarrelTransform = owner->getCurrentWeaponMeshComponent()->GetBoneTransform(boneIndex);
	FTransform ammoTransform = this->calculateAmmoTransform(weaponBarrelTransform);
	FTransform visibleAmmoTransform = this->calculateVisibleAmmoTransform(weaponBarrelTransform, ammoTransform);
	ALostConnectionGameState* gameState = Utility::getGameState(owner.Get());

	for (size_t i = 0; i < shotsCount; i++)
	{
		if (currentMagazineSize >= ammoCost)
		{
			float currentSpreadDistance = this->calculateSpreadDistance();
			float pitch = FMath::RandRange(-currentSpreadDistance, currentSpreadDistance);
			float yaw = FMath::Tan(FMath::Acos(pitch / currentSpreadDistance)) * pitch;
			AAmmo* launchedAmmo = gameState->spawn<AAmmo>(ammoClass, ammoTransform);
			
			launchedAmmo->copyProperties(this);

			launchedAmmo->launch(owner, visibleAmmoTransform, { pitch, FMath::RandRange(-yaw, yaw), 0.0f });

			currentMagazineSize -= ammoCost;

			currentAccuracyMultiplier += drawback;

			currentTimeBetweenShots += timeBetweenShots;
		}
		else
		{
			MultiplayerUtility::runOnServerReliableWithMulticast(owner.Get(), "reload");

			break;
		}
	}
}

UBaseWeapon::UBaseWeapon() :
	currentMagazineSize(0),
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
	static constexpr float decreaseAccuracyMultiplier = 0.95f;
	bool isReloading = owner->getIsReloading();

	if (isReloading)
	{
		currentTimeBetweenShots = 0.0f;
	}
	else if (isShooting)
	{
		currentTimeBetweenShots -= DeltaTime;
	}
	else if (currentTimeBetweenShots)
	{
		currentTimeBetweenShots = FMath::Max(0.0f, currentTimeBetweenShots - DeltaTime);
	}

	currentAccuracyMultiplier = FMath::Max(1.0f, currentAccuracyMultiplier * decreaseAccuracyMultiplier);

	if (!isReloading && isShooting && currentTimeBetweenShots <= 0.0f)
	{
		this->shoot();
	}
}

void UBaseWeapon::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void UBaseWeapon::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void UBaseWeapon::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void UBaseWeapon::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
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

void UBaseWeapon::setAddedDamage_Implementation(float newAddedDamage)
{
	addedDamage = newAddedDamage;
}

void UBaseWeapon::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
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

float UBaseWeapon::getAddedDamage() const
{
	return addedDamage;
}

float UBaseWeapon::getAdditionalDamage() const
{
	return additionalDamage;
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

float UBaseWeapon::getLength() const
{
	return length;
}
