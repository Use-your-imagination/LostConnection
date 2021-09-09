// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "UObject/ConstructorHelpers.h"

ABullet::ABullet()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> ammoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/Bullet.Bullet'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> brokenAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BulletBroken.BulletBroken'"));

	if (ammoMeshFinder.Succeeded())
	{
		mesh->SetStaticMesh(ammoMeshFinder.Object);
	}

	if (brokenAmmoMeshFinder.Succeeded())
	{
		brokenAmmoMesh = brokenAmmoMeshFinder.Object;
	}

	movement->InitialSpeed = 5200.0f;
	movement->MaxSpeed = 5200.0f;

	damage = 75;
	ammoType = ammoTypes::small;
}
