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

	DOREPLIFETIME(UBaseWeapon, currentMagazineSize);

	DOREPLIFETIME(UBaseWeapon, magazineSize);

	DOREPLIFETIME(UBaseWeapon, weaponType);
}

void UBaseWeapon::shoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
{
	ABaseCharacter* baseCharacter = Cast<ABaseCharacter>(character);

	if (weaponType == weaponTypes::semiAutomatic || weaponType == weaponTypes::single)
	{
		MultiplayerUtility::runOnServerReliable(baseCharacter, "resetShoot");
	}
	else if (weaponType == weaponTypes::delay)
	{
		return;
	}

	if (currentMagazineSize >= ammoCost)
	{
		ABaseAmmo* launchedAmmo = baseCharacter->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ABaseAmmo>(ammo->getStaticClass(), FTransform(currentVisibleWeaponMesh->GetBoneLocation("barrel")));

		launchedAmmo->copyProperties(ammo);

		// Tracer limit
		static constexpr float distance = 20000.0f;

		FHitResult hit;
		FRotator resultRotation;
		ABaseDrone* drone = Cast<ABaseDrone>(baseCharacter);

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
			resultRotation = baseCharacter->getCurrentWeaponMesh()->GetBoneLocation("barrel").ToOrientationRotator();
		}

		launchedAmmo->getAmmoMeshComponent()->SetWorldRotation(resultRotation);

		float pitch = FMath::RandRange(-spreadDistance, spreadDistance);
		float yaw = FMath::Tan(FMath::Acos(pitch / spreadDistance)) * pitch;

		launchedAmmo->getAmmoMeshComponent()->AddRelativeRotation({ pitch, FMath::RandRange(-yaw, yaw), 0.0f });

		launchedAmmo->launch(baseCharacter);

		currentMagazineSize -= ammoCost;
	}
	else
	{
		MultiplayerUtility::runOnServerReliableWithMulticast(baseCharacter, "reload");
	}
}

UBaseWeapon::UBaseWeapon()
{
	shootRemainingTime = 0.0f;
	clearTimer = false;

	ammoCost = 1;
	weaponType = weaponTypes::automatic;
	spreadDistance = 2.0f;
}

void UBaseWeapon::shoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
{
	FTimerManager& manager = world->GetTimerManager();

	if (manager.IsTimerActive(shootHandle))
	{
		return;
	}
	else
	{
		clearTimer = false;
	}

	FTimerDelegate delegate;

	delegate.BindLambda([this, &manager, currentVisibleWeaponMesh, character]()
		{
			if (character->IsPendingKill())
			{
				return;
			}

			if (clearTimer || currentVisibleWeaponMesh->SkeletalMesh != mesh)
			{
				clearTimer = false;

				manager.ClearTimer(shootHandle);

				return;
			}

			this->shoot(currentVisibleWeaponMesh, character);
		});

	manager.SetTimer(shootHandle, delegate, 1.0f / static_cast<float>(rateOfFire), true, shootRemainingTime > 0.0f ? shootRemainingTime : 0.0f);

	shootRemainingTime = 1.0f / static_cast<float>(rateOfFire);
}

void UBaseWeapon::resetShoot(UWorld* world, USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
{
	clearTimer = true;

	if (weaponType == weaponTypes::delay)
	{
		weaponType = weaponTypes::single;

		this->shoot(world, currentVisibleWeaponMesh, character);

		weaponType = weaponTypes::delay;
	}
}

void UBaseWeapon::alternativeMode()
{
	
}

void UBaseWeapon::reduceShootRemainigTime_Implementation(float deltaSeconds)
{
	if (shootRemainingTime > 0.0f)
	{
		shootRemainingTime -= deltaSeconds;
	}
}

void UBaseWeapon::setCurrentMagazineSize(int currentMagazineSize)
{
	this->currentMagazineSize = currentMagazineSize;
}

void UBaseWeapon::setRateOfFire(int rateOfFire)
{
	this->rateOfFire = rateOfFire;
}

void UBaseWeapon::setWeaponType(weaponTypes weaponType)
{
	this->weaponType = weaponType;
}

USkeletalMesh* UBaseWeapon::getWeaponMesh() const
{
	return mesh;
}

UStaticMesh* UBaseWeapon::getMagazineMesh() const
{
	return magazineMesh;
}

ABaseAmmo* UBaseWeapon::getAmmo() const
{
	return ammo;
}

int UBaseWeapon::getCurrentMagazineSize() const
{
	return currentMagazineSize;
}

int UBaseWeapon::getMagazineSize() const
{
	return magazineSize;
}

int UBaseWeapon::getRateOfFire() const
{
	return rateOfFire;
}

weaponTypes UBaseWeapon::getWeaponType() const
{
	return weaponType;
}
