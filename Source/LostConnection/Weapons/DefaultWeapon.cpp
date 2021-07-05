// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultWeapon.h"

#include "../Ammo/DefaultAmmo.h"

ADefaultWeapon::ADefaultWeapon()
{
	mesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Assets/Weapons/Rifle/Rifle.Rifle'")));

	ammo = NewObject<ADefaultAmmo>();

	currentMagazineSize = 30;
	magazineSize = 30;
	rateOfFire = 20;
	weaponType = weaponTypes::automatic;
}
