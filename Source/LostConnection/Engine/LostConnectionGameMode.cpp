// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include "LostConnectionGameState.h"
#include "LostConnectionPlayerController.h"

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
	static ConstructorHelpers::FClassFinder<APawn> defaultPawnClassFinder(TEXT("/Game/Drones/SN4K3/BP_SN4K3"));
	static ConstructorHelpers::FClassFinder<APawn> defaultAIClassFinder(TEXT("/Game/AI/Enemies/EnemyBlueprints/Default/BP_DefaultEnemy"));
	static ConstructorHelpers::FClassFinder<APlayerState> defaultPlayerStateClassFinder(TEXT("/Game/Engine/BP_LostConnectionPlayerState"));
	
	bUseSeamlessTravel = true;
	DefaultPawnClass = defaultPawnClassFinder.Class;
	PlayerControllerClass = ALostConnectionPlayerController::StaticClass();
	PlayerStateClass = defaultPlayerStateClassFinder.Class;
	GameStateClass = ALostConnectionGameState::StaticClass();
}

void ALostConnectionGameMode::spawnAI_Implementation(int32 count) const
{
	spawner.spawn(GetWorld(), count);
}
