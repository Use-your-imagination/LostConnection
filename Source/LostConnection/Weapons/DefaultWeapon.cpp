// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultWeapon.h"

#include "UObject/ConstructorHelpers.h"

#include "Ammo/DefaultAmmo.h"

UDefaultWeapon::UDefaultWeapon()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> defaultWeaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/Pistols/Gauss/Gauss.Gauss'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> defaultMagazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Pistols/Gauss/GaussMagazine.GaussMagazine'"));

	if (defaultWeaponMeshFinder.Succeeded())
	{
		mesh = defaultWeaponMeshFinder.Object;
	}

	if (defaultMagazineFinder.Succeeded())
	{
		magazineMesh = defaultMagazineFinder.Object;
	}

	ammo = NewObject<ADefaultAmmo>();

	currentMagazineSize = 30;
	magazineSize = 30;
	rateOfFire = 20;
	weaponType = weaponTypes::automatic;
}
