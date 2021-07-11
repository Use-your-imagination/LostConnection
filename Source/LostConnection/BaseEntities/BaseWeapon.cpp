#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"

#include "Engine/LostConnectionGameState.h"
#include "Character/LostConnectionCharacter.h"

#pragma warning(disable: 4458)

void ABaseWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

ABaseWeapon::ABaseWeapon()
{
	ammoCost = 1;
	weaponType = weaponTypes::automatic;
	spreadDistance = 2.0f;
}

void ABaseWeapon::shoot(USkeletalMeshComponent* currentVisibleWeaponMesh, ACharacter* character)
{
	if (weaponType == weaponTypes::semiAutomatic)
	{
		Cast<ALostConnectionCharacter>(character)->resetShoot();
	}

	if (currentMagazineSize >= ammoCost)
	{
		ABaseAmmo* launchedAmmo = character->GetWorld()->GetGameState<ALostConnectionGameState>()->spawn<ABaseAmmo>(ammo->getStaticClass(), currentVisibleWeaponMesh->GetBoneLocation("barrel"), { 0.0f, 0.0f, 0.0f });

		launchedAmmo->getAmmoMesh()->AddRelativeRotation(character->GetActorRotation());

		float pitch = FMath::RandRange(-spreadDistance, spreadDistance);
		float yaw = FMath::Tan(FMath::Acos(pitch / spreadDistance)) * pitch;

		launchedAmmo->getAmmoMesh()->AddRelativeRotation({ pitch, FMath::RandRange(-yaw, yaw), 0.0f });

		launchedAmmo->launch(character);

		currentMagazineSize -= ammoCost;
	}
	else
	{
		Cast<ALostConnectionCharacter>(character)->reload();
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

int ABaseWeapon::getRateOfFire() const
{
	return rateOfFire;
}

weaponTypes ABaseWeapon::getWeaponType() const
{
	return weaponType;
}

float ABaseWeapon::getFlatDamageReduction_Implementation() const
{
	return 0.0f;
}

float ABaseWeapon::getPercentageDamageReduction_Implementation() const
{
	return 1.0f;
}
