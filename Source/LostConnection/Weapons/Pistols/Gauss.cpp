// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauss.h"

#include "UObject/ConstructorHelpers.h"

#include "Ammo/Bullets/Ball.h"

UGauss::UGauss()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> weaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/Pistols/Gauss/Gauss.Gauss'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> magazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Pistols/Gauss/GaussMagazine.GaussMagazine'"));

	mesh = weaponMeshFinder.Object;

	magazineMesh = magazineFinder.Object;

	ammoType = ammoTypes::defaultType;
	damage = 150.0f;
	currentMagazineSize = 12;
	magazineSize = 12;
	roundsPerSecond = 2;
	weaponType = weaponTypes::single;
	spreadDistance = 0.1f;
	ammoClass = ABall::StaticClass();

	this->updateTimeBetweenShots();
}
