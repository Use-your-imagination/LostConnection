// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "UObject/ConstructorHelpers.h"

ABall::ABall()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> ammoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BallBullet.BallBullet'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> brokenAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BallBulletBroken.BallBulletBroken'"));

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
	ammoType = ammoTypes::defaultType;
}
