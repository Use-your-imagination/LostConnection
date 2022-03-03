// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "Characters/Drones/SN4K3/SN4K3.h"

void ALostConnectionPlayerController::GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList)
{
	ActorList.Add(GetPawn());

	Super::GetSeamlessTravelActorList(bToEntry, ActorList);
}

ALostConnectionPlayerController::ALostConnectionPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	NetUpdateFrequency = UConstants::actorNetUpdateFrequency;
}

void ALostConnectionPlayerController::respawnPlayer_Implementation(const FTransform& respawnTransform)
{
	APawn* pawn = GetPawn();
	FTransform spawnTransform(respawnTransform);
	ALostConnectionPlayerState* playerState = GetPlayerState<ALostConnectionPlayerState>();

	pawn->Destroy();

	ABaseDrone* drone = Utility::getGameState(this)->spawn<ABaseDrone>
	(
		Utility::findDroneClass
		(
			ULostConnectionAssetManager::get().getDrones(),
			playerState->getDroneClass()
		),
		spawnTransform
	);

	Possess(drone);

	drone->FinishSpawning({}, true);

	playerState->restoreRespawnCooldown();
}

void ALostConnectionPlayerController::save_Implementation()
{

}
