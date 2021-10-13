#include "Hipter.h"

#include "Ammo/Bullets/Bullet.h"

UHipter::UHipter()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> weaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/SubmachineGuns/Hipter/Hipter.Hipter'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> magazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/SubmachineGuns/Hipter/HipterMagazine.HipterMagazine'"));

	mesh = weaponMeshFinder.Object;

	magazineMesh = magazineFinder.Object;

	ammoType = ammoTypes::small;
	damage = 55.0f;
	currentMagazineSize = 150;
	magazineSize = 150;
	roundsPerSecond = 30;
	weaponType = weaponTypes::automatic;
	spreadDistance = 0.25f;
	ammoClass = ABullet::StaticClass();

	this->updateTimeBetweenShots();
}
