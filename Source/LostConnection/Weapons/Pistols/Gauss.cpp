// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauss.h"

#include "UObject/ConstructorHelpers.h"

#include "Ammo/Ball.h"

UGauss::UGauss()
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

	currentMagazineSize = 30;
	magazineSize = 30;
	rateOfFire = 20;
	weaponType = weaponTypes::single;
}
