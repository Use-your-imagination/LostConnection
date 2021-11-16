#include "Ball.h"

#include "UObject/ConstructorHelpers.h"

ABall::ABall()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ammoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BallBullet.BallBullet'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> brokenAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BallBulletBroken.BallBulletBroken'"));

	mesh->SetStaticMesh(ammoMeshFinder.Object);

	brokenAmmoMesh = brokenAmmoMeshFinder.Object;
}
