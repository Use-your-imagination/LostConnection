#include "Bullet.h"

#include "UObject/ConstructorHelpers.h"

ABullet::ABullet()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ammoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/Bullet.Bullet'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> brokenAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BulletBroken.BulletBroken'"));

	mesh->SetStaticMesh(ammoMeshFinder.Object);

	brokenAmmoMesh = brokenAmmoMeshFinder.Object;
}
