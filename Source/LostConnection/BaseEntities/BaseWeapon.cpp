#include "BaseWeapon.h"

#include "../Engine/LostConnectionPlayerState.h"

#pragma warning(disable: 4458)

ABaseWeapon::ABaseWeapon()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	ammoCost = 1;
}

bool ABaseWeapon::shoot(USkeletalMeshComponent* currentVisibleWeaponMesh)
{
	if (character)
	{
		if (currentMagazineSize)
		{
			ALostConnectionPlayerState* playerState = Cast<APlayerController>(character->GetController())->GetPlayerState<ALostConnectionPlayerState>();

			playerState->spawn<ABaseAmmo>(ammo->getStaticClass(), currentVisibleWeaponMesh->GetBoneLocation("BBarrel_end"), FRotator(0.0f, 0.0f, 0.0f))->getAmmoMesh()->AddRelativeRotation(character->GetActorRotation());

			currentMagazineSize -= ammoCost;
		}
		else
		{
			return false;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, L"character is nullptr");
	}

	return true;
}

void ABaseWeapon::setCurrentMagazineSize(int currentMagazineSize)
{
	this->currentMagazineSize = currentMagazineSize;
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

float ABaseWeapon::getFlatDamageReduction_Implementation() const
{
	return 0.0f;
}

float ABaseWeapon::getPercentageDamageReduction_Implementation() const
{
	return 1.0f;
}
