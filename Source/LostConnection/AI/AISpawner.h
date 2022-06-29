// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

class LOSTCONNECTION_API AISpawner
{
private:
	FActorSpawnParameters spawnParameters;

public:
	AISpawner();

	void spawn(TObjectPtr<UWorld> world, int32 waveNumber) const;

	~AISpawner() = default;
};
