// Copyright (c) 2021 Use Your Imagination

#include "AISpawner.h"

#include "Kismet/GameplayStatics.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Characters/AI/BaseBot.h"
#include "WorldPlaceables/AI/AISpawnPoint.h"
#include "Utility/Utility.h"
#include "WorldPlaceables/AI/WavesController.h"

AISpawner::AISpawner()
{
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AISpawner::spawn(TObjectPtr<AWavesController> wavesController, int32 waveNumber) const
{
	TMap<EBotType, TArray<TObjectPtr<AAISpawnPoint>>> spawnPointsByType;
	const FWaveSettings& waveSettings = wavesController->getWaveSettings(waveNumber);
	const UBaseActDataAsset& currentAct = ULostConnectionAssetManager::get().getCurrentAct();

	for (int32 i = 0; i < StaticCast<int32>(EBotType::size); i++)
	{
		spawnPointsByType.Emplace(StaticCast<EBotType>(i));
	}

	{
		TArray<TObjectPtr<AActor>> spawnPoints;

		UGameplayStatics::GetAllActorsOfClass(wavesController, AAISpawnPoint::StaticClass(), spawnPoints);

		for (const TObjectPtr<AActor>& tem : spawnPoints)
		{
			TObjectPtr<AAISpawnPoint> spawnPoint = Cast<AAISpawnPoint>(tem);

			spawnPointsByType[spawnPoint->getBotSpawnType()].Add(spawnPoint);
		}
	}

	for (const TPair<EBotType, int32>& pair : waveSettings.botsPerType)
	{
		const TArray<TSubclassOf<ABaseBot>>& bots = currentAct[pair.Key];
		const TArray<TObjectPtr<AAISpawnPoint>>& spawnPoints = spawnPointsByType[pair.Key];

		for (int32 i = 0; i < pair.Value; i++)
		{
			const auto& spawnPoint = Utility::getRandomValueFromArray(spawnPoints);

			wavesController->GetWorld()->SpawnActor<ABaseBot>(Utility::getRandomValueFromArray(bots), spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation(), spawnParameters);
		}
	}
}
