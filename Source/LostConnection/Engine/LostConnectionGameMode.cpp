// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include "LostConnectionGameState.h"
#include "LostConnectionPlayerController.h"
#include "Constants/Constants.h"

#pragma warning(disable: 4458)

void ALostConnectionGameMode::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	ActorList.Reserve(GameState->PlayerArray.Num());
	
	ActorList.Append(GameState->PlayerArray);
	
	if (bToTransition)
	{
		ActorList.Add(this);
	
		ActorList.Add(GameState);
	}

	Super::GetSeamlessTravelActorList(bToTransition, ActorList);
}

ALostConnectionGameMode::ALostConnectionGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> defaultPawnClassFinder(TEXT("/Game/WorldPlaceable/BP_PreConnectionPlaceholder"));
	static ConstructorHelpers::FClassFinder<APlayerState> defaultPlayerStateClassFinder(TEXT("/Game/Engine/BP_LostConnectionPlayerState"));
	static ConstructorHelpers::FClassFinder<APlayerController> defaultPlayerControllerClassFinder(TEXT("/Game/Engine/BP_LostConnectionPlayerController"));
	
	bUseSeamlessTravel = true;

	NetUpdateFrequency = UConstants::minNetUpdateFrequency;

	DefaultPawnClass = defaultPawnClassFinder.Class;
	PlayerControllerClass = defaultPlayerControllerClassFinder.Class;
	PlayerStateClass = defaultPlayerStateClassFinder.Class;
	GameStateClass = ALostConnectionGameState::StaticClass();
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

void ALostConnectionGameMode::HandleSeamlessTravelPlayer(AController*& controller)
{
	Super::HandleSeamlessTravelPlayer(controller);
}
