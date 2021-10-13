// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "UObject/ConstructorHelpers.h"

ABullet::ABullet()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> ammoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/Bullet.Bullet'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> brokenAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BulletBroken.BulletBroken'"));

	mesh->SetStaticMesh(ammoMeshFinder.Object);

	brokenAmmoMesh = brokenAmmoMeshFinder.Object;
}
