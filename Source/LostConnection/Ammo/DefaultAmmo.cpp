// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAmmo.h"

#include "UObject/ConstructorHelpers.h"

ADefaultAmmo::ADefaultAmmo()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> defaultAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/Bullet.Bullet'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> brokenAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BulletBroken.BulletBroken'"));

	if (defaultAmmoMeshFinder.Succeeded())
	{
		mesh->SetStaticMesh(defaultAmmoMeshFinder.Object);
	}

	if (brokenAmmoMeshFinder.Succeeded())
	{
		brokenAmmoMesh = brokenAmmoMeshFinder.Object;
	}

	movement->InitialSpeed = 5200.0f;
	movement->MaxSpeed = 5200.0f;

	damage = 75;
	ammoType = ammoTypes::defaultType;
}
