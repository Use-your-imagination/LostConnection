// Copyright (c) 2022 Use Your Imagination

#include "AISpawnManager.h"

#include "Kismet/GameplayStatics.h"

#include "Characters/BaseBot.h"

bool AISpawnManager::isBotsAlreadySpawned(UWorld* world)
{
	TArray<AActor*> tem;

	UGameplayStatics::GetAllActorsOfClass(world, ABaseBot::StaticClass(), tem);

	return StaticCast<bool>(tem.Num());
}

void AISpawnManager::process(UWorld* world)
{
	if (!remainingAIToSpawn || AISpawnManager::isBotsAlreadySpawned(world))
	{
		return;
	}

	currentWaveTotalBots = 0;

	if (remainingWaves != 1)
	{
		currentWaveTotalBots = spawnPerWave;
	}
	else
	{
		currentWaveTotalBots = remainingAIToSpawn;
	}

	currentWaveRemainingBots = currentWaveTotalBots;

	spawner.spawn(world, currentWaveTotalBots);

	remainingWaves--;
}

void AISpawnManager::init(int32 totalCount, int32 waves)
{
	remainingAIToSpawn = totalCount;
	remainingWaves = waves;

	spawnPerWave = totalCount / waves;
}

void AISpawnManager::notify(UWorld* world)
{
	remainingAIToSpawn--;
	currentWaveRemainingBots--;

	this->process(world);
}

int32 AISpawnManager::getRemainingAIToSpawn() const
{
	return remainingAIToSpawn;
}

int32 AISpawnManager::getRemainingWaves() const
{
	return remainingWaves;
}

int32 AISpawnManager::getCurrentWaveTotalBots() const
{
	return currentWaveTotalBots;
}

int32 AISpawnManager::getCurrentWaveRemainingBots() const
{
	return currentWaveRemainingBots;
}
