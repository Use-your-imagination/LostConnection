#include "Hipter.h"

#include "Ammo/Bullets/Bullet.h"

UHipter::UHipter()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> weaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/SubmachineGuns/Hipter/Hipter.Hipter'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> magazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/SubmachineGuns/Hipter/HipterMagazine.HipterMagazine'"));

	if (weaponMeshFinder.Succeeded())
	{
		mesh = weaponMeshFinder.Object;
	}

	if (magazineFinder.Succeeded())
	{
		magazineMesh = magazineFinder.Object;
	}

	ammo = NewObject<ABullet>();

	ammo->setDamage(55.0f);

	ammo->setAmmoType(ammoTypes::small);

	currentMagazineSize = 150;
	magazineSize = 150;
	roundsPerSecond = 30;
	weaponType = weaponTypes::automatic;
	spreadDistance = 0.25f;
	
	this->updateTimeBetweenShots();
}

void UHipter::alternativeMode()
{
	
}
