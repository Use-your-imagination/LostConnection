// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "UObject/ConstructorHelpers.h"

ABall::ABall()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> ammoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BallBullet.BallBullet'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> brokenAmmoMeshFinder(TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/BallBulletBroken.BallBulletBroken'"));

	mesh->SetStaticMesh(ammoMeshFinder.Object);

	brokenAmmoMesh = brokenAmmoMeshFinder.Object;
}
