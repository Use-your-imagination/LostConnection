// Copyright (c) 2021 Use Your Imagination

#include "LostConnectionPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "Characters/Drones/SN4K3/SN4K3.h"
#include "WorldPlaceables/Raid/TeleportPoint.h"

void ALostConnectionPlayerController::GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& ActorList)
{
	ActorList.Add(GetPawn());

	Super::GetSeamlessTravelActorList(bToEntry, ActorList);
}

void ALostConnectionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionPlayerController, lootManager);
}

void ALostConnectionPlayerController::onLootManagerInit()
{
	lootManager->init(this);
}

void ALostConnectionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		lootManager = GetWorld()->SpawnActor<ALootManager>();

		this->onLootManagerInit();
	}
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

void ALostConnectionPlayerController::setMainTeleportFromLoadedRoom_Implementation(ATeleportPoint* teleportPoint)
{
	mainTeleportFromLoadedRoom = teleportPoint;

	if (IsValid(teleportPoint))
	{
		Utility::getGameState(this)->notifyLevelLoading();
	}
}

const TObjectPtr<ATeleportPoint> ALostConnectionPlayerController::getMainTeleportFromLoadedRoom() const
{
	return mainTeleportFromLoadedRoom;
}
