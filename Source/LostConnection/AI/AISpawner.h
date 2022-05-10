// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

class LOSTCONNECTION_API AISpawner
{
private:
	FActorSpawnParameters spawnParameters;

public:
	AISpawner();

	void spawn(UWorld* world, int32 count) const;

	~AISpawner() = default;
};
