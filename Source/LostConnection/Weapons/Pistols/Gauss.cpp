// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauss.h"

#include "UObject/ConstructorHelpers.h"

#include "Ammo/Bullets/Ball.h"

AGauss::AGauss()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> weaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/Pistols/Gauss/Gauss.Gauss'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> magazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Pistols/Gauss/GaussMagazine.GaussMagazine'"));

	if (weaponMeshFinder.Succeeded())
	{
		mesh = weaponMeshFinder.Object;
	}

	if (magazineFinder.Succeeded())
	{
		magazineMesh = magazineFinder.Object;
	}

	ammo = NewObject<ABall>();

	ammo->setDamage(150.0f);

	ammo->setAmmoType(ammoTypes::defaultType);

	currentMagazineSize = 12;
	magazineSize = 12;
	roundsPerSecond = 2;
	weaponType = weaponTypes::single;
	spreadDistance = 0.1f;
	
	this->updateTimeBetweenShots();
}
