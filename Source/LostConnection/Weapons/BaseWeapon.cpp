#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"

#include "Utility/MultiplayerUtility.h"
#include "Engine/LostConnectionPlayerState.h"
#include "Engine/LostConnectionGameState.h"
#include "Characters/BaseDrone.h"
#include "Characters/BaseBot.h"

#pragma warning(disable: 4458)

void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseWeapon, ammo);

	DOREPLIFETIME(ABaseWeapon, currentMagazineSize);

	DOREPLIFETIME(ABaseWeapon, magazineSize);

	DOREPLIFETIME(ABaseWeapon, ammoCost);

	DOREPLIFETIME(ABaseWeapon, roundsPerSecond);

	DOREPLIFETIME(ABaseWeapon, weaponType);

	DOREPLIFETIME(ABaseWeapon, spreadDistance);
}

bool ABaseWeapon::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(ammo, *Bunch, *RepFlags);

	return wroteSomething;
}

void ABaseWeapon::shoot()
{
	if (character->getIsReloading() && !character->isWeaponEquipped())
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
		ABaseAmmo* launchedAmmo = character->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ABaseAmmo>(ammo->getStaticClass(), FTransform(character->getCurrentWeaponMesh()->GetBoneLocation("barrel")));

		launchedAmmo->copyProperties(ammo);

		// Tracer limit
		static constexpr float distance = 20000.0f;

		FHitResult hit;
		FRotator resultRotation;
		ABaseDrone* drone = Cast<ABaseDrone>(character);

		if (drone)
		{
			FVector start = drone->GetFollowCamera()->GetComponentLocation();
			FVector end = start + drone->GetFollowCamera()->GetComponentRotation().Vector() * distance;

			if (drone->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Visibility))
			{
				resultRotation = (hit.Location - drone->getCurrentWeaponMesh()->GetBoneLocation("barrel")).ToOrientationRotator();
			}
			else
			{
				resultRotation = ((drone->GetFollowCamera()->GetComponentRotation().Vector() * distance) - drone->getCurrentWeaponMesh()->GetBoneLocation("barrel")).ToOrientationRotator();
			}
		}
		else
		{
			resultRotation = character->getCurrentWeaponMesh()->GetBoneLocation("barrel").ToOrientationRotator();
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

ABaseWeapon::ABaseWeapon() :
	ammoCost(1)
{
	
}

void ABaseWeapon::startShoot()
{
	isShooting = true;
}

void ABaseWeapon::resetShoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
{
	isShooting = false;

	if (weaponType == weaponTypes::delay)
	{
		weaponType = weaponTypes::single;

		this->shoot();

		weaponType = weaponTypes::delay;
	}
}

void ABaseWeapon::alternativeMode()
{

}

void ABaseWeapon::updateTimeBetweenShots_Implementation()
{
	timeBetweenShots = 1.0f / static_cast<float>(roundsPerSecond);
}

void ABaseWeapon::setWorld(UWorld* world)
{
	this->world = world;
}

void ABaseWeapon::setCharacter(ABaseCharacter* character)
{
	this->character = character;
}

void ABaseWeapon::setCurrentMagazineSize_Implementation(int newCurrentMagazineSize)
{
	currentMagazineSize = newCurrentMagazineSize;
}

void ABaseWeapon::setRateOfFire_Implementation(int newRoundsPerSecond)
{
	roundsPerSecond = newRoundsPerSecond;
}

void ABaseWeapon::setWeaponType_Implementation(weaponTypes newWeaponType)
{
	weaponType = newWeaponType;
}

USkeletalMesh* ABaseWeapon::getWeaponMesh() const
{
	return mesh;
}

UStaticMesh* ABaseWeapon::getMagazineMesh() const
{
	return magazineMesh;
}

ABaseAmmo* ABaseWeapon::getAmmo() const
{
	return ammo;
}

int ABaseWeapon::getCurrentMagazineSize() const
{
	return currentMagazineSize;
}

int ABaseWeapon::getMagazineSize() const
{
	return magazineSize;
}

int ABaseWeapon::getRoundsPerSecond() const
{
	return roundsPerSecond;
}

weaponTypes ABaseWeapon::getWeaponType() const
{
	return weaponType;
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isShooting)
	{
		this->shoot();
	}

	if (currentTimeBetweenShots > 0.0f)
	{
		currentTimeBetweenShots -= DeltaTime;

		if (currentTimeBetweenShots < 0.0f)
		{
			currentTimeBetweenShots = 0.0f;
		}
	}
}
