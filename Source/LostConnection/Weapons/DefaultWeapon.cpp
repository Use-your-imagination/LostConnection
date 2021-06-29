// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultWeapon.h"

#include "../Ammo/DefaultAmmo.h"

ADefaultWeapon::ADefaultWeapon()
{
	mesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Assets/Weapons/Rifle/Rifle.Rifle'")));

	ammo = NewObject<ADefaultAmmo>();
}
