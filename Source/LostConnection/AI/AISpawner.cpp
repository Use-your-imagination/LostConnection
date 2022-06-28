// Copyright (c) 2021 Use Your Imagination

#include "AISpawner.h"

#include "Kismet/GameplayStatics.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Characters/AI/BaseBot.h"
#include "WorldPlaceables/AI/AISpawnPoint.h"
#include "Utility/Utility.h"

AISpawner::AISpawner()
{
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AISpawner::spawn(UWorld* world, int32 count) const
{
	const TArray<TSubclassOf<ABaseBot>>& bots = ULostConnectionAssetManager::get().getCurrentAct()[EBotType::ranged];
	TArray<TObjectPtr<AActor>> spawnPoints;

	UGameplayStatics::GetAllActorsOfClass(world, AAISpawnPoint::StaticClass(), spawnPoints);

	for (int32 i = 0; i < count; i++)
	{
		const auto& spawnPoint = Utility::getRandomValueFromArray(spawnPoints);

		world->SpawnActor<ABaseBot>(Utility::getRandomValueFromArray(bots), spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation(), spawnParameters);
	}
}
