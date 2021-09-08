// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedWeapon.h"

#include "Character/LostConnectionCharacter.h"

ADroppedWeapon::ADroppedWeapon()
{
	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine"));

	magazine->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	magazine->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	magazine->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	magazine->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
}

void ADroppedWeapon::setWeapon(UBaseWeapon* weapon)
{
	this->weapon = weapon;

	this->setMesh(weapon->getWeaponMesh());

	magazine->AttachToComponent(mesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), "magazine");
	
	magazine->SetStaticMesh(weapon->getMagazineMesh());
}

void ADroppedWeapon::action(AActor* player)
{
	Cast<ALostConnectionCharacter>(player)->pickupWeapon(this);
}

UBaseWeapon* ADroppedWeapon::getWeapon()
{
	return weapon;
}
