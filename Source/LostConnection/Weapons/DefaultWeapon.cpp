// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultWeapon.h"

ADefaultWeapon::ADefaultWeapon()
{
	mesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/LostConnection/Meshes/Linear_Stair_StaticMesh.Linear_Stair_StaticMesh'")));
}
