#include "BaseAmmo.h"

#pragma warning(disable: 4458)

ABaseAmmo::ABaseAmmo()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
}

void ABaseAmmo::setAmmoMesh(UStaticMesh* mesh)
{
	this->mesh->SetStaticMesh(mesh);
}
