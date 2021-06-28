#include "BaseWeapon.h"

void ABaseWeapon::BeginPlay()
{
	AActor::BeginPlay();


}

ABaseWeapon::ABaseWeapon()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
}

USkeletalMesh* ABaseWeapon::getWeaponMesh() const
{
	return mesh->SkeletalMesh;
}
