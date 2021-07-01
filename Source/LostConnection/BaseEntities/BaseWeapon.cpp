#include "BaseWeapon.h"

#include "../Engine/LostConnectionPlayerState.h"

ABaseWeapon::ABaseWeapon()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
}

void ABaseWeapon::shoot(USkeletalMeshComponent* currentVisibleWeaponMesh)
{
	if (character)
	{
		ALostConnectionPlayerState* playerState = Cast<APlayerController>(character->GetController())->GetPlayerState<ALostConnectionPlayerState>();

		playerState->spawn<ABaseAmmo>(ammo->getStaticClass(), currentVisibleWeaponMesh->GetBoneLocation("Bone_end"), FRotator(0.0f, 0.0f, 0.0f))->getAmmoMesh()->AddRelativeRotation(character->GetActorRotation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, L"character is nullptr");
	}
}

USkeletalMesh* ABaseWeapon::getWeaponMesh() const
{
	return mesh->SkeletalMesh;
}

float ABaseWeapon::getFlatDamageReduction_Implementation() const
{
	return 0.0f;
}

float ABaseWeapon::getPercentageDamageReduction_Implementation() const
{
	return 1.0f;
}

