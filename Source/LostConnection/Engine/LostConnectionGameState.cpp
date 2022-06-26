// Copyright (c) 2021 Use Your Imagination

#include "LostConnectionGameState.h"

#include "Algo/ForEach.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "WorldPlaceables/Utility/LevelCreationWaypoint.h"
#include "Utility/Utility.h"
#include "Constants/Constants.h"
#include "LostConnectionGameMode.h"
#include "Loot/LootManager.h"
#include "WorldPlaceables/Utility/AISpawnPoint.h"
#include "WorldPlaceables/Raid/ChooseRoomConsole.h"
#include "WorldPlaceables/Raid/TeleportPoint.h"

void ALostConnectionGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALostConnectionGameState, totalBots);

	DOREPLIFETIME(ALostConnectionGameState, totalWaves);

	DOREPLIFETIME(ALostConnectionGameState, remainingBots);

	DOREPLIFETIME(ALostConnectionGameState, remainingWaves);

	DOREPLIFETIME(ALostConnectionGameState, currentWaveTotalBots);

	DOREPLIFETIME(ALostConnectionGameState, currentWaveRemainingBots);
}

void ALostConnectionGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	manager = NewObject<UVFXManager>(this);
}

void ALostConnectionGameState::loadRoom_Implementation(const TSoftObjectPtr<UWorld>& room, const FTransform& spawnTransform)
{
	lastLoadedRoom = room;

	ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, lastLoadedRoom, spawnTransform, isRoomLoaded);
}

void ALostConnectionGameState::clearRoom()
{
	TArray<TObjectPtr<AActor>> aiSpawnPoints;

	UGameplayStatics::GetAllActorsOfClass(this, AAISpawnPoint::StaticClass(), aiSpawnPoints);

	if (TObjectPtr<AActor> roomConsole = UGameplayStatics::GetActorOfClass(this, AChooseRoomConsole::StaticClass()))
	{
		roomConsole->Destroy();
	}

	for (TObjectPtr<AActor> aiSpawnPoint : aiSpawnPoints)
	{
		aiSpawnPoint->Destroy();
	}
}

void ALostConnectionGameState::spawnVFXAtLocationMulticast_Implementation(const FVector& location, UNiagaraSystem* vfx)
{
	manager->spawnVFX(GetWorld(), location, vfx);
}

void ALostConnectionGameState::spawnVFXAtTransformMulticast_Implementation(const FTransform& transform, UNiagaraSystem* vfx)
{
	manager->spawnVFX(GetWorld(), transform, vfx);
}

void ALostConnectionGameState::giveEachPlayerLootPoints_Implementation(int32 count)
{
	for (APlayerState* playerState : PlayerArray)
	{
		Cast<ALostConnectionPlayerState>(playerState)->increaseLootPoints(count);
	}
}

ALostConnectionGameState::ALostConnectionGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	NetUpdateFrequency = UConstants::minNetUpdateFrequency;
}

void ALostConnectionGameState::startRoomLoading_Implementation()
{
	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();
	const UBaseActDataAsset& act = manager.getCurrentAct();
	TArray<TSoftObjectPtr<UWorld>> rooms = act.getRooms();
	TObjectPtr<AActor> waypoint = UGameplayStatics::GetActorOfClass(this, ALevelCreationWaypoint::StaticClass());
	FTransform spawnTransform = waypoint->GetActorTransform();

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

	waypoint->Destroy();

	this->clearRoom();

	this->loadRoom(Utility::getRandomValueFromArray(rooms), MoveTemp(spawnTransform));
}

void ALostConnectionGameState::spawnVFXAtLocation_Implementation(const FVector& location, UNiagaraSystem* vfx)
{
	this->spawnVFXAtLocationMulticast(location, vfx);
}

void ALostConnectionGameState::spawnVFXAtTransform_Implementation(const FTransform& transform, UNiagaraSystem* vfx)
{
	this->spawnVFXAtTransformMulticast(transform, vfx);
}

void ALostConnectionGameState::verteilenLootPoints(ILootPointsGiver* giver)
{
	if (!giver || !IsValid(giver->_getUObject()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Failed to receive loot points"));

		return;
	}

	int32 lootPointsFromGiver = giver->getLootPoints();

	this->giveEachPlayerLootPoints(lootPointsFromGiver);
}

void ALostConnectionGameState::dropAmmo(IAmmoDropable* ammoDropable)
{
	check(HasAuthority());

	TArray<AActor*> managers;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALootManager::StaticClass(), managers);

	for (const auto& i : managers)
	{
		TObjectPtr<ALootManager> manager = Cast<ALootManager>(i);

		manager->spawnAmmoCall(ammoDropable->_getUObject());
	}
}

void ALostConnectionGameState::notifyLevelLoading_Implementation()
{
	TArray<TObjectPtr<AActor>> actors;
	TArray<TObjectPtr<ALostConnectionPlayerController>> controllers;

	UGameplayStatics::GetAllActorsOfClass(this, ALostConnectionPlayerController::StaticClass(), actors);

	for (TObjectPtr<AActor> actor : actors)
	{
		TObjectPtr<ALostConnectionPlayerController> controller = Cast<ALostConnectionPlayerController>(actor);

		if (controller->getMainTeleportFromLoadedRoom().IsNull())
		{
			return;
		}

		controllers.Add(MoveTemp(controller));
	}

	for (TObjectPtr<ALostConnectionPlayerController> controller : controllers)
	{
		controller->getMainTeleportFromLoadedRoom()->teleport(controller);

		controller->setMainTeleportFromLoadedRoom(nullptr);
	}
}

int32& ALostConnectionGameState::getTotalBots()
{
	return totalBots;
}

int32& ALostConnectionGameState::getTotalWaves()
{
	return totalWaves;
}

int32& ALostConnectionGameState::getRemainingBots()
{
	return remainingBots;
}

int32& ALostConnectionGameState::getRemainingWaves()
{
	return remainingWaves;
}

int32& ALostConnectionGameState::getCurrentWaveTotalBots()
{
	return currentWaveTotalBots;
}

int32& ALostConnectionGameState::getCurrentWaveRemainingBots()
{
	return currentWaveRemainingBots;
}

const TSoftObjectPtr<UWorld>& ALostConnectionGameState::getLastLoadedRoom() const
{
	return lastLoadedRoom;
}

void ALostConnectionGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		TObjectPtr<ALostConnectionGameMode> gameMode = GetWorld()->GetAuthGameMode<ALostConnectionGameMode>();

		if (!gameMode)
		{
			return;
		}

		AISpawnManager& spawnManager = gameMode->getSpawnManager();

		remainingBots = spawnManager.getRemainingAIToSpawn();

		remainingWaves = spawnManager.getRemainingWaves();

		currentWaveTotalBots = spawnManager.getCurrentWaveTotalBots();

		currentWaveRemainingBots = spawnManager.getCurrentWaveRemainingBots();
	}
}
