// Copyright (c) 2022 Use Your Imagination

#include "WavesController.h"

#include "NavigationSystem.h"

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

	if (TObjectPtr<UNavigationSystemV1> navigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		navigationSystem->Build();
	}

	spawnManager.init(this);

	Utility::getGameState(this)->getTotalWaves() = this->getWaveCount();

	spawnManager.notify();
}

AWavesController::AWavesController()
{
	PrimaryActorTick.bCanEverTick = false;

	navigation = CreateDefaultSubobject<UNavigationInvokerComponent>("Navigation");

	navigation->SetGenerationRadii(10'000.0f, 10'000.0f);
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

FWaveSettings& AWavesController::operator [] (int32 waveNumber)
{
	return waveSettings[waveNumber];
}

int32 AWavesController::getWaveCount() const
{
	return waveSettings.Num();
}

AISpawnManager& AWavesController::getSpawnManager()
{
	return spawnManager;
}
