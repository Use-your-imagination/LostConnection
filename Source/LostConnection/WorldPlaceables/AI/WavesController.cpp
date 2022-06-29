// Copyright (c) 2022 Use Your Imagination

#include "WavesController.h"

#include "Utility/Utility.h"
#include "AI/AISpawnManager.h"

void AWavesController::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		Destroy();

		return;
	}

	spawnManager.init(this);

	Utility::getGameState(this)->getTotalWaves() = this->getWaveCount();

	spawnManager.notify();
}

AWavesController::AWavesController()
{
	PrimaryActorTick.bCanEverTick = false;
}

const FWaveSettings& AWavesController::getWaveSettings(int32 waveNumber) const
{
	return waveSettings[waveNumber];
}

void AWavesController::notify()
{
	TObjectPtr<ALostConnectionGameState> gameState = Utility::getGameState(this);

	gameState->getRemainingBots() = spawnManager.getRemainingBots();

	gameState->getRemainingWaves() = spawnManager.getRemainingWaves();

	gameState->getCurrentWaveTotalBots() = spawnManager.getCurrentWaveTotalBots();

	gameState->getCurrentWaveRemainingBots() = spawnManager.getCurrentWaveRemainingBots();
}

int32 AWavesController::getWaveCount() const
{
	return waveSettings.Num();
}

AISpawnManager& AWavesController::getSpawnManager()
{
	return spawnManager;
}
