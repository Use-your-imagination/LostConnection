// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAmmo.h"

ADefaultAmmo::ADefaultAmmo()
{
	mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Assets/Weapons/Ammo/Bullet.Bullet'")));

	mesh->SetWorldScale3D(FVector(10.0f));

	damage = 500;
}
