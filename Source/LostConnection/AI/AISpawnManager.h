// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "AISpawner.h"

#pragma warning(disable: 4458)

class LOSTCONNECTION_API AISpawnManager
{
private:
	AISpawner spawner;
	int32 remainingAIToSpawn;
	int32 remainingWaves;
	int32 spawnPerWave;
	int32 currentWaveTotalBots;
	int32 currentWaveRemainingBots;

private:
	static bool isBotsAlreadySpawned(UWorld* world);

private:
	void process(UWorld* world);

public:
	AISpawnManager() = default;

	void init(int32 totalCount, int32 waves);

	void notify(UWorld* world);

	int32 getRemainingAIToSpawn() const;

	int32 getRemainingWaves() const;

	int32 getCurrentWaveTotalBots() const;

	int32 getCurrentWaveRemainingBots() const;

	~AISpawnManager() = default;

	friend class ALostConnectionGameMode;
};
