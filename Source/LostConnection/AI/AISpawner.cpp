// Copyright (c) 2021 Use Your Imagination

#include "AISpawner.h"

#include "Kismet/GameplayStatics.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Characters/BaseBot.h"
#include "WorldPlaceables/Utility/AISpawnPoint.h"
#include "Utility/Utility.h"

AISpawner::AISpawner()
{
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AISpawner::spawn(UWorld* world, int32 count) const
{
	const TArray<TSubclassOf<ABaseBot>>& bots = ULostConnectionAssetManager::get().getCurrentAct().getBots();
	TArray<AActor*> spawnPoints;

	UGameplayStatics::GetAllActorsOfClass(world, AAISpawnPoint::StaticClass(), spawnPoints);

	for (int32 i = 0; i < count; i++)
	{
		const TSubclassOf<ABaseBot>& botClass = Utility::getRandomValueFromArray(bots);
		const auto& spawnPoint = Utility::getRandomValueFromArray(spawnPoints);

		world->SpawnActor<ABaseBot>(botClass, spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation(), spawnParameters);
	}
}
