// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultWeapon.h"

#include "UObject/ConstructorHelpers.h"

#include "Ammo/DefaultAmmo.h"

ADefaultWeapon::ADefaultWeapon()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> defaultWeaponMeshFinder(TEXT("SkeletalMesh'/Game/Assets/Weapons/Rifle/Rifle.Rifle'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> defaultMagazineFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Rifle/RifleMagazine.RifleMagazine'"));

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
