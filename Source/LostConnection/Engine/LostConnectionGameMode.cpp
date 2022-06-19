// Copyright (c) 2021 Use Your Imagination

#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "AIController.h"

#include "LostConnectionGameState.h"
#include "LostConnectionPlayerState.h"
#include "LostConnectionPlayerController.h"
#include "Constants/Constants.h"
#include "Utility/Utility.h"

#pragma warning(disable: 4458)

void ALostConnectionGameMode::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	for (TObjectPtr<APlayerState> state : GameState->PlayerArray)
	{
		if (!state->GetPlayerController())
		{
			continue;
		}

		ActorList.Add(Cast<ALostConnectionPlayerState>(state)->getInventory());
	}

	Super::GetSeamlessTravelActorList(bToTransition, ActorList);
}

void ALostConnectionGameMode::BeginPlay()
{
	Super::BeginPlay();
}

ALostConnectionGameMode::ALostConnectionGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> pawnClassFinder(TEXT("/Game/WorldPlaceable/BP_PreConnectionPlaceholder"));
	static ConstructorHelpers::FClassFinder<APlayerState> playerStateClassFinder(TEXT("/Game/Engine/BP_LostConnectionPlayerState"));
	static ConstructorHelpers::FClassFinder<AGameState> gameStateClassFinder(TEXT("/Game/Engine/BP_LostConnectionGameState"));
	static ConstructorHelpers::FClassFinder<APlayerController> playerControllerClassFinder(TEXT("/Game/Engine/BP_LostConnectionPlayerController"));

	bUseSeamlessTravel = true;

	NetUpdateFrequency = UConstants::minNetUpdateFrequency;

	DefaultPawnClass = pawnClassFinder.Class;
	PlayerControllerClass = playerControllerClassFinder.Class;
	PlayerStateClass = playerStateClassFinder.Class;
	GameStateClass = gameStateClassFinder.Class;
}

void ALostConnectionGameMode::initRoomAI(int32 totalCount, int32 waves)
{
	ALostConnectionGameState* gameState = GetGameState<ALostConnectionGameState>();

	gameState->getTotalBots() = totalCount;

	gameState->getTotalWaves() = waves;

	spawnManager.init(totalCount, waves);

	spawnManager.process(GetWorld());
}

AISpawnManager& ALostConnectionGameMode::getSpawnManager()
{
	return spawnManager;
}

void ALostConnectionGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
}

void ALostConnectionGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	if (C->IsA<AAIController>())
	{
		C->GetPlayerState<ALostConnectionPlayerState>()->Destroy();

		C->Destroy();

		return;
	}

	TArray<TObjectPtr<AActor>> inventories;
	TObjectPtr<ALostConnectionPlayerState> playerState = C->GetPlayerState<ALostConnectionPlayerState>();
	TObjectPtr<AInventory> travelledInventory;

	UGameplayStatics::GetAllActorsOfClass(this, AInventory::StaticClass(), inventories);

	for (TObjectPtr<AActor> tem : inventories)
	{
		TObjectPtr<AInventory> inventory = Cast<AInventory>(tem);

		if (inventory->getPlayerState() == playerState)
		{
			travelledInventory = inventory;

			break;
		}
	}

	Super::HandleSeamlessTravelPlayer(C);

	playerState = C->GetPlayerState<ALostConnectionPlayerState>();

	playerState->setInventory(travelledInventory);

	travelledInventory->init(playerState);
}
