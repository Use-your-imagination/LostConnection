#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"

#include "Engine/LostConnectionGameState.h"
#include "Character/LostConnectionCharacter.h"

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
}

UBaseWeapon::UBaseWeapon()
{
	ammoCost = 1;
	weaponType = weaponTypes::automatic;
	spreadDistance = 2.0f;
}

void UBaseWeapon::shoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
{
	ALostConnectionCharacter* lostCharacter = Cast<ALostConnectionCharacter>(character);

	if (weaponType == weaponTypes::semiAutomatic)
	{
		lostCharacter->resetShoot();
	}

	if (currentMagazineSize >= ammoCost)
	{
		ABaseAmmo* launchedAmmo = lostCharacter->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ABaseAmmo>(ammo->getStaticClass(), currentVisibleWeaponMesh->GetBoneLocation("barrel"), { 0.0f, 0.0f, 0.0f });

		// TODO: getter for distance
		float distance = 20000.0f;

		FHitResult hit;
		FVector start = lostCharacter->GetFollowCamera()->GetComponentLocation();
		FVector end = start + lostCharacter->GetFollowCamera()->GetComponentRotation().Vector() * distance;
		FRotator resultRotation;

		if (lostCharacter->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Visibility))
		{
			resultRotation = (hit.Location - lostCharacter->getCurrentWeaponMesh()->GetBoneLocation("barrel")).ToOrientationRotator();
		}
		else
		{
			resultRotation = ((lostCharacter->GetFollowCamera()->GetComponentRotation().Vector() * distance) - lostCharacter->getCurrentWeaponMesh()->GetBoneLocation("barrel")).ToOrientationRotator();
		}

		launchedAmmo->getAmmoMesh()->SetWorldRotation(resultRotation);

		float pitch = FMath::RandRange(-spreadDistance, spreadDistance);
		float yaw = FMath::Tan(FMath::Acos(pitch / spreadDistance)) * pitch;

		launchedAmmo->getAmmoMesh()->AddRelativeRotation({ pitch, FMath::RandRange(-yaw, yaw), 0.0f });

		launchedAmmo->launch(lostCharacter);

		currentMagazineSize -= ammoCost;
	}
	else
	{
		lostCharacter->reload();
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
