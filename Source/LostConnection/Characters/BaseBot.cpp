// Copyright (c) 2021 Use-your-imagination

#include "BaseBot.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"

#include "Weapons/Pistols/Gauss.h"
#include "Engine/LostConnectionGameMode.h"
#include "Statuses/Ailments/SwarmAilment.h"

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
	UWorld* world = GetWorld();

	if (!isAlly)
	{
		world->GetGameState<ALostConnectionGameState>()->verteilenLootPoints(this);
	}

	Destroy();

	if (!isAlly)
	{
		world->GetAuthGameMode<ALostConnectionGameMode>()->getSpawnManager().notify(world);
	}
}

ABaseBot::ABaseBot()
{
	isAlly = false;
}

int32 ABaseBot::getLootPoints() const
{
	return lootPointsReward;
}
