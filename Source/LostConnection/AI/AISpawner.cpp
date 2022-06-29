// Copyright (c) 2021 Use Your Imagination

#include "AISpawner.h"

#include "Kismet/GameplayStatics.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Characters/AI/BaseBot.h"
#include "WorldPlaceables/AI/AISpawnPoint.h"
#include "WorldPlaceables/AI/AISpawnManagerSettings.h"
#include "Utility/Utility.h"

AISpawner::AISpawner()
{
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AISpawner::spawn(TObjectPtr<UWorld> world, int32 waveNumber) const
{
	TObjectPtr<AAISpawnManagerSettings> settings = Cast<AAISpawnManagerSettings>(UGameplayStatics::GetActorOfClass(world, AAISpawnManagerSettings::StaticClass()));
	TArray<TObjectPtr<AActor>> spawnPoints;
	const FWaveSettings& waveSettings = settings->getWaveSettings(waveNumber);

	UGameplayStatics::GetAllActorsOfClass(world, AAISpawnPoint::StaticClass(), spawnPoints);

	for (const TPair<EBotType, int32>& pair : waveSettings.botsPerType)
	{
		const TArray<TSubclassOf<ABaseBot>>& bots = ULostConnectionAssetManager::get().getCurrentAct()[pair.Key];

		// TODO: Find valid spawn points

		for (int32 i = 0; i < pair.Value; i++)
		{
			const auto& spawnPoint = Utility::getRandomValueFromArray(spawnPoints);

			world->SpawnActor<ABaseBot>(Utility::getRandomValueFromArray(bots), spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation(), spawnParameters);
		}
	}
}
