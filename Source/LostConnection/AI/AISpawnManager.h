// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "AISpawner.h"

#pragma warning(disable: 4458)

class LOSTCONNECTION_API AISpawnManager
{
private:
	AISpawner spawner;
	TObjectPtr<class AWavesController> wavesController;
	int32 currentWave;
	int32 currentWaveRemainingBots;

private:
	void process();

	void updateCurrentWaveRemainingBots();

	TArray<TObjectPtr<AActor>> getDrones() const;

	void processBeginEvents() const;

	void processEndEvents() const;

public:
	AISpawnManager() = default;

	void init(TObjectPtr<class AWavesController> wavesController);

	void notify();

	int32 getRemainingBots() const;

	int32 getRemainingWaves() const;

	int32 getCurrentWaveTotalBots() const;

	int32 getCurrentWaveRemainingBots() const;

	~AISpawnManager() = default;

	friend class AWavesController;
};
