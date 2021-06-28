#include "BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}

UStaticMesh* ABaseWeapon::getWeaponMesh() const
{
	return mesh->GetStaticMesh();
}
