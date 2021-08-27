// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedWeapon.h"

ADroppedWeapon::ADroppedWeapon()
{
	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));

	magazine->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	magazine->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ADroppedWeapon::setWeapon(UBaseWeapon* weapon)
{
	this->weapon = weapon;

	this->setMesh(weapon->getWeaponMesh());

	magazine->AttachToComponent(mesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), "magazine");
	
	magazine->SetStaticMesh(weapon->getMagazineMesh());
}
