#include "Gauss.h"

#include "UObject/ConstructorHelpers.h"

#include "Ammo/Bullets/Ball.h"

UGauss::UGauss()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> weaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/Pistols/Gauss/Gauss.Gauss'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> magazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Pistols/Gauss/GaussMagazine.GaussMagazine'"));
	ConstructorHelpers::FClassFinder<UAnimInstance> animBPFinder(TEXT("/Game/Assets/Weapons/Pistols/Gauss/AnimBP_Gauss"));

	mesh = weaponMeshFinder.Object;

	magazineMesh = magazineFinder.Object;

	animationBlueprint = animBPFinder.Class;

	ammoType = ammoTypes::defaultType;
	damageType = typeOfDamage::physical;
	damage = 150.0f;
	currentMagazineSize = 12;
	magazineSize = 12;
	roundsPerSecond = 2;
	weaponType = weaponTypes::single;
	spreadDistance = 0.1f;
	ammoClass = ABall::StaticClass();

	this->updateTimeBetweenShots();
}
