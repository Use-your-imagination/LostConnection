// Copyright (c) 2022 Use-your-imagination

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

	int32 spawnCount = 0;

	if (remainingWaves != 1)
	{
		spawnCount = spawnPerWave;
	}
	else
	{
		spawnCount = remainingAIToSpawn;
	}

	spawner.spawn(world, spawnCount);

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
