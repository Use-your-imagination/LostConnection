// Copyright (c) 2021 Use-your-imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"
#include "AIController.h"

#include "Weapons/Pistols/Gauss.h"
#include "Engine/LostConnectionGameMode.h"
#include "Statuses/Ailments/SwarmAilment.h"
#include "Loot/LootManager.h"

void ABaseBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBot::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		this->changeToDefaultWeapon();
	}
}

void ABaseBot::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseBot, lootPointsReward);
}

void ABaseBot::deathLogic()
{
	TObjectPtr<UWorld> world = GetWorld();
	TObjectPtr<ALostConnectionGameState> gameState = world->GetGameState<ALostConnectionGameState>();

	if (!isAlly)
	{
		gameState->verteilenLootPoints(this);
	}

	gameState->dropAmmo(this);

	this->destroyAssociatedActors();

	if (!isAlly)
	{
		world->GetAuthGameMode<ALostConnectionGameMode>()->getSpawnManager().notify(world);
	}
}

void ABaseBot::destroyAssociatedActors()
{
	TObjectPtr<AAIController> controller = GetController<AAIController>();
	TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(this);
	TObjectPtr<AInventory> inventory = playerState->getInventory();

	inventory->Destroy();

	playerState->Destroy();

	controller->UnPossess();

	controller->Destroy();

	Destroy();
}

ABaseBot::ABaseBot() :
	smallAmmoDropChance(45.0f),
	largeAmmoDropChance(45.0f),
	energyAmmoDropChance(45.0f)
{
	isAlly = false;
}

int32 ABaseBot::getLootPoints() const
{
	return lootPointsReward;
}

float ABaseBot::getSmallAmmoDropChance() const
{
	return smallAmmoDropChance;
}

float ABaseBot::getLargeAmmoDropChance() const
{
	return largeAmmoDropChance;
}

float ABaseBot::getEnergyAmmoDropChance() const
{
	return energyAmmoDropChance;
}
