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

		ABaseAmmo* newAmmo = playerState->spawn<ABaseAmmo>(ammo->getStaticClass(), currentVisibleWeaponMesh->GetBoneLocation("Bone_end"), FRotator(0.0f, 0.0f, 0.0f));
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
