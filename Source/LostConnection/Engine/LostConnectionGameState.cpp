// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionGameState.h"

#include "Algo/ForEach.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "WorldPlaceables/Utility/LevelCreationWaypoint.h"
#include "Utility/Utility.h"
#include "Constants/Constants.h"

void ALostConnectionGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionGameState, isLastRoomLoaded);
}

void ALostConnectionGameState::loadRoom(const TSoftObjectPtr<UWorld>& room, FVector location, FRotator rotation)
{
	ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, room, location, rotation, isLastRoomLoaded);
}

ALostConnectionGameState::ALostConnectionGameState()
{
	NetUpdateFrequency = UConstants::minNetUpdateFrequency;
}

void ALostConnectionGameState::startRoomLoading_Implementation()
{
	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();
	const UBaseActDataAsset& act = manager.getCurrentAct();
	TArray<TSoftObjectPtr<UWorld>> rooms = act.getRooms();
	AActor* waypoint = UGameplayStatics::GetActorOfClass(this, ALevelCreationWaypoint::StaticClass());
	
	Algo::ForEachIf
	(
		usedRooms,
		[&rooms](const TSoftObjectPtr<UWorld>& room) { return rooms.Find(room) != INDEX_NONE; },
		[&rooms](const TSoftObjectPtr<UWorld>& room) { rooms.Remove(room); }
	);

	if (!rooms.Num())
	{
		rooms = MoveTemp(usedRooms);
	}

	const TSoftObjectPtr<UWorld>& room = Utility::getRandomValueFromArray(rooms);
	
	this->loadRoom(room, waypoint->GetActorLocation(), waypoint->GetActorRotation());

	waypoint->Destroy();
}
