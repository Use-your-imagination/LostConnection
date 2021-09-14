#include "Hipter.h"

#include "Ammo/Bullet.h"

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

	currentMagazineSize = 30;
	magazineSize = 30;
	rateOfFire = 20;
	weaponType = weaponTypes::automatic;
}

void UHipter::alternativeMode()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, L"Hipter");
}
