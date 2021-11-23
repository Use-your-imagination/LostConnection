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
}

void UBaseWeapon::shoot()
{
	if (ownerCharacter->getIsReloading())
	{
		return;
	}

	if (weaponType == weaponTypes::semiAutomatic || weaponType == weaponTypes::single)
	{
		MultiplayerUtility::runOnServerReliable(ownerCharacter.Get(), "resetShoot");
	}
	else if (weaponType == weaponTypes::delay)
	{
		return;
	}

	if (currentMagazineSize >= ammoCost)
	{
		ABaseAmmo* launchedAmmo = Utility::getGameState(ownerCharacter.Get())->spawn<ABaseAmmo>(ammoClass, FTransform(ownerCharacter->getCurrentWeaponMeshComponent()->GetBoneLocation("barrel")));

		launchedAmmo->copyProperties(this);

		FHitResult hit;
		FRotator resultRotation;
		ABaseDrone* drone = Cast<ABaseDrone>(ownerCharacter.Get());

		if (drone)
		{
			// Tracer limit
			static constexpr float distance = 20000.0f;

			FVector start = drone->getStartActionLineTrace();
			FVector end = start + drone->GetFollowCamera()->GetComponentRotation().Vector() * distance;
			
			if (drone->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Visibility))
			{
				resultRotation = (hit.Location - drone->getCurrentWeaponMeshComponent()->GetBoneLocation("barrel")).ToOrientationRotator();
			}
			else
			{
				resultRotation = ((drone->GetFollowCamera()->GetComponentRotation().Vector() * distance) - drone->getCurrentWeaponMeshComponent()->GetBoneLocation("barrel")).ToOrientationRotator();
			}
		}
		else
		{
			ABaseBot* bot = Cast<ABaseBot>(ownerCharacter.Get());
			AAIController* controller = bot->GetController<AAIController>();
			ABaseDrone* target = Cast<ABaseDrone>(controller->GetBlackboardComponent()->GetValueAsObject("Drone"));

			if (target && target->IsValidLowLevelFast())
			{
				FVector targetLocation = target->GetActorLocation();

				resultRotation = (targetLocation - bot->GetActorLocation()).ToOrientationRotator();
			}
		}

		launchedAmmo->getAmmoMeshComponent()->SetWorldRotation(resultRotation);

		float pitch = FMath::RandRange(-spreadDistance, spreadDistance);
		float yaw = FMath::Tan(FMath::Acos(pitch / spreadDistance)) * pitch;

		launchedAmmo->getAmmoMeshComponent()->AddRelativeRotation({ pitch, FMath::RandRange(-yaw, yaw), 0.0f });

		launchedAmmo->launch(ownerCharacter.Get());

		currentMagazineSize -= ammoCost;

		currentTimeBetweenShots = timeBetweenShots;
	}
	else
	{
		MultiplayerUtility::runOnServerReliableWithMulticast(ownerCharacter.Get(), "reload");
	}
}

UBaseWeapon::UBaseWeapon() :
	ammoCost(1)
{

}

void UBaseWeapon::startShoot()
{
	isShooting = true;
}

void UBaseWeapon::resetShoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
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
	timeBetweenShots = 1.0f / static_cast<float>(roundsPerSecond);
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

void UBaseWeapon::setWorld(UWorld* world)
{
	this->world = world;
}

void UBaseWeapon::setOwnerCharacter(ABaseCharacter* ownerCharacter)
{
	this->ownerCharacter = ownerCharacter;
}

void UBaseWeapon::setAmmoType_Implementation(ammoTypes newAmmoType)
{
	ammoType = newAmmoType;
}

void UBaseWeapon::setDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UBaseWeapon::setCurrentMagazineSize_Implementation(int newCurrentMagazineSize)
{
	currentMagazineSize = newCurrentMagazineSize;
}

void UBaseWeapon::setRateOfFire_Implementation(int newRoundsPerSecond)
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

float UBaseWeapon::getDamage() const
{
	return damage;
}

int UBaseWeapon::getCurrentMagazineSize() const
{
	return currentMagazineSize;
}

int UBaseWeapon::getMagazineSize() const
{
	return magazineSize;
}

int UBaseWeapon::getRoundsPerSecond() const
{
	return roundsPerSecond;
}

weaponTypes UBaseWeapon::getWeaponType() const
{
	return weaponType;
}

UClass* UBaseWeapon::getAnimationBlueprint() const
{
	return animationBlueprint;
}

const TWeakObjectPtr<ABaseCharacter>& UBaseWeapon::getOwnerCharacter() const
{
	return ownerCharacter;
}

float UBaseWeapon::getCrushingHitChance() const
{
	return crushingHitChance;
}

float UBaseWeapon::getAdditionalCrushingHitChance() const
{
	return additionalCrushingHitChance;
}
