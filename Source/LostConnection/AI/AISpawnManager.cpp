// Copyright (c) 2022 Use Your Imagination

#include "AISpawnManager.h"

#include "Kismet/GameplayStatics.h"
#include "Algo/Count.h"
#include "Algo/Accumulate.h"

#include "Characters/AI/BaseBot.h"
#include "WorldPlaceables/AI/WavesController.h"

void AISpawnManager::process()
{
	if (currentWaveRemainingBots || (wavesController->getWaveCount() == currentWave + 1))
	{
		return;
	}

	spawner.spawn(wavesController, ++currentWave);
}

void AISpawnManager::updateCurrentWaveRemainingBots()
{
	TArray<TObjectPtr<AActor>> bots;

	UGameplayStatics::GetAllActorsOfClass(wavesController, ABaseBot::StaticClass(), bots);

	currentWaveRemainingBots = Algo::CountIf(bots, [](TObjectPtr<AActor> bot) { return !Cast<ABaseBot>(bot)->getIsAlly(); });
}

void AISpawnManager::init(TObjectPtr<AWavesController> wavesController)
{
	currentWave = -1;

	this->wavesController = wavesController;

	this->updateCurrentWaveRemainingBots();
}

void AISpawnManager::notify()
{
	this->updateCurrentWaveRemainingBots();

	this->process();

	this->updateCurrentWaveRemainingBots();

	wavesController->notify();
}

int32 AISpawnManager::getRemainingBots() const
{
	return currentWave == -1 ? 0 : [this]() -> int32
	{
		TArray<int32> values;

		for (int32 i = currentWave + 1; i < wavesController->getWaveCount(); i++)
		{
			TArray<int32> tem;

			wavesController->getWaveSettings(i).botsPerType.GenerateValueArray(tem);

			values.Append(tem);
		}

		return Algo::Accumulate(values, 0) + currentWaveRemainingBots;
	}();
}

int32 AISpawnManager::getRemainingWaves() const
{
	return currentWave == -1 ?
		wavesController->getWaveCount() :
		wavesController->getWaveCount() - currentWave - 1;
}

int32 AISpawnManager::getCurrentWaveTotalBots() const
{
	return currentWave == -1 ? 0 : [this]() -> int32
	{
		TArray<int32> values;

		wavesController->getWaveSettings(currentWave).botsPerType.GenerateValueArray(values);

		return Algo::Accumulate(values, 0);
	}();
}

int32 AISpawnManager::getCurrentWaveRemainingBots() const
{
	return currentWaveRemainingBots;
}
