// Copyright (c) 2021 Use Your Imagination

#include "DroppedWeapon.h"

#include "Net/UnrealNetwork.h"

#include "Characters/BaseDrone.h"

#include "Characters/BaseDrone.h"

void ADroppedWeapon::onWeaponChange()
{
	if (weapon)
	{
		this->setMesh(weapon->getWeaponMesh());
	}
}

void ADroppedWeapon::Tick(float DeltaSeconds)
{
	if (HasAuthority())
	{
		weapon->Tick(DeltaSeconds);
	}
}

void ADroppedWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADroppedWeapon, weapon);
}

bool ADroppedWeapon::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(weapon))
	{
		wroteSomething |= Channel->ReplicateSubobject(weapon, *Bunch, *RepFlags);

		wroteSomething |= weapon->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

void ADroppedWeapon::action(TObjectPtr<ABaseDrone> player)
{
	player->pickupWeapon(this);
}

ADroppedWeapon::ADroppedWeapon()
{
	magazine = CreateDefaultSubobject<UStaticMeshComponent>("Magazine");

	magazine->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	magazine->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	magazine->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	magazine->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
}

void ADroppedWeapon::setWeapon_Implementation(UBaseWeapon* newWeapon)
{
	weapon = DuplicateObject<UBaseWeapon>(newWeapon, this);

	this->setMesh(weapon->getWeaponMesh());
}

UBaseWeapon* ADroppedWeapon::getWeapon()
{
	return weapon;
}

void ADroppedWeapon::setMesh(USkeletalMesh* mesh)
{
	this->mesh->SetSkeletalMesh(mesh);

	magazine->AttachToComponent(this->mesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), "magazine");

	magazine->SetStaticMesh(weapon->getMagazineMesh());
}
