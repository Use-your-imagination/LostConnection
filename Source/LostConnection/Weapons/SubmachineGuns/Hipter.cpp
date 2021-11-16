#include "Hipter.h"

#include "Ammo/Bullets/Bullet.h"

UHipter::UHipter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> weaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/SubmachineGuns/Hipter/Hipter.Hipter'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> magazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/SubmachineGuns/Hipter/HipterMagazine.HipterMagazine'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> animBPFinder(TEXT("/Game/Assets/Weapons/SubmachineGuns/Hipter/AnimBP_Hipter"));

	mesh = weaponMeshFinder.Object;

	magazineMesh = magazineFinder.Object;

	animationBlueprint = animBPFinder.Class;

	ammoType = ammoTypes::small;
	damageType = typeOfDamage::physical;
	damage = 55.0f;
	currentMagazineSize = 150;
	magazineSize = 150;
	roundsPerSecond = 30;
	weaponType = weaponTypes::automatic;
	spreadDistance = 0.25f;
	ammoClass = ABullet::StaticClass();

	this->updateTimeBetweenShots();
}
