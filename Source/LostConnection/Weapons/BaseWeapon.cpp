#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"

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

	DOREPLIFETIME(UBaseWeapon, damage);

	DOREPLIFETIME(UBaseWeapon, currentMagazineSize);

	DOREPLIFETIME(UBaseWeapon, magazineSize);

	DOREPLIFETIME(UBaseWeapon, ammoCost);

	DOREPLIFETIME(UBaseWeapon, roundsPerSecond);

	DOREPLIFETIME(UBaseWeapon, weaponType);

	DOREPLIFETIME(UBaseWeapon, spreadDistance);
}

void UBaseWeapon::shoot()
{
	if (character->getIsReloading())
	{
		return;
	}

	if (weaponType == weaponTypes::semiAutomatic || weaponType == weaponTypes::single)
	{
		MultiplayerUtility::runOnServerReliable(character, "resetShoot");
	}
	else if (weaponType == weaponTypes::delay)
	{
		return;
	}

	if (currentMagazineSize >= ammoCost)
	{
		ABaseAmmo* launchedAmmo = character->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ABaseAmmo>(ammoClass, FTransform(character->getCurrentWeaponMeshComponent()->GetBoneLocation("barrel")));

		launchedAmmo->copyProperties(this);

		FHitResult hit;
		FRotator resultRotation;
		ABaseDrone* drone = Cast<ABaseDrone>(character);

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
			resultRotation = character->getCurrentWeaponMeshComponent()->GetComponentRotation().Vector().ToOrientationRotator();

			resultRotation.Yaw = character->GetCapsuleComponent()->GetComponentRotation().Yaw;
		}

		launchedAmmo->getAmmoMeshComponent()->SetWorldRotation(resultRotation);

		float pitch = FMath::RandRange(-spreadDistance, spreadDistance);
		float yaw = FMath::Tan(FMath::Acos(pitch / spreadDistance)) * pitch;

		launchedAmmo->getAmmoMeshComponent()->AddRelativeRotation({ pitch, FMath::RandRange(-yaw, yaw), 0.0f });

		launchedAmmo->launch(character);

		currentMagazineSize -= ammoCost;

		currentTimeBetweenShots = timeBetweenShots;
	}
	else
	{
		MultiplayerUtility::runOnServerReliableWithMulticast(character, "reload");
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

void UBaseWeapon::setCharacter(ABaseCharacter* character)
{
	this->character = character;
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
