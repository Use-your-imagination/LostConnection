#include "BaseWeapon.h"

#include "../Engine/LostConnectionPlayerState.h"
#include "../Character/LostConnectionCharacter.h"

#pragma warning(disable: 4458)

ABaseWeapon::ABaseWeapon()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	ammoCost = 1;
}

void ABaseWeapon::shoot(USkeletalMeshComponent* currentVisibleWeaponMesh)
{
	if (character)
	{
		if (currentMagazineSize >= ammoCost)
		{
			ALostConnectionPlayerState* playerState = Cast<APlayerController>(character->GetController())->GetPlayerState<ALostConnectionPlayerState>();

			playerState->spawn<ABaseAmmo>(ammo->getStaticClass(), currentVisibleWeaponMesh->GetBoneLocation("BBarrel_end"), FRotator(0.0f, 0.0f, 0.0f))->getAmmoMesh()->AddRelativeRotation(character->GetActorRotation());

			currentMagazineSize -= ammoCost;
		}
		else
		{
			ALostConnectionCharacter* tem = Cast<ALostConnectionCharacter>(character);

			tem->reload();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, L"character is nullptr");
	}
}

void ABaseWeapon::setCurrentMagazineSize(int currentMagazineSize)
{
	this->currentMagazineSize = currentMagazineSize;
}

void ABaseWeapon::setRateOfFire(int rateOfFire)
{
	this->rateOfFire = rateOfFire;
}

USkeletalMesh* ABaseWeapon::getWeaponMesh() const
{
	return mesh->SkeletalMesh;
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

int ABaseWeapon::getRateOfFire() const
{
	return rateOfFire;
}

float ABaseWeapon::getFlatDamageReduction_Implementation() const
{
	return 0.0f;
}

float ABaseWeapon::getPercentageDamageReduction_Implementation() const
{
	return 1.0f;
}
