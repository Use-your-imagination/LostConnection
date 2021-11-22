// Copyright (c) 2021 Use-your-imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"

#include "Weapons/Pistols/Gauss.h"

void ABaseBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBot::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UWorld* world = GetWorld();

		if (world)
		{
			defaultWeaponSlot = NewObject<UGauss>(this);

			defaultWeaponSlot->setWorld(world);

			defaultWeaponSlot->setOwnerCharacter(this);
		}

		this->changeToDefaultWeapon();
	}
}

void ABaseBot::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABaseBot::deathLogic()
{
	Destroy();
}

ABaseBot::ABaseBot()
{
	isAlly = false;

	spareAmmo.Init(9999, 4);
}
