// Copyright (c) 2022 Use Your Imagination

#include "AISpawnManager.h"

#include "Kismet/GameplayStatics.h"

#include "Characters/AI/BaseBot.h"
#include "WorldPlaceables/AI/AISpawnManagerSettings.h"

bool AISpawnManager::isBotsAlreadySpawned(TObjectPtr<UWorld> world)
{
	TArray<TObjectPtr<AActor>> tem;

	UGameplayStatics::GetAllActorsOfClass(world, ABaseBot::StaticClass(), tem);

	return StaticCast<bool>(tem.Num());
}

void AISpawnManager::process(TObjectPtr<UWorld> world)
{
	if (AISpawnManager::isBotsAlreadySpawned(world))
	{
		return;
	}

	TObjectPtr<AAISpawnManagerSettings> settings = Cast<AAISpawnManagerSettings>(UGameplayStatics::GetActorOfClass(world, AAISpawnManagerSettings::StaticClass()));

	if (settings->getWaveCount() == currentWave)
	{
		return;
	}

	spawner.spawn(world, currentWave++);
}

void AISpawnManager::init(int32 totalCount, int32 waves)
{
	currentWave = 0;

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
