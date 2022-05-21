// Copyright (c) 2022 Use Your Imagination

#include "RoomActorsSpawner.h"

#include "Utility/Utility.h"
#include "Constants/Constants.h"

void ARoomActorsSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		Destroy();

		return;
	}

	TObjectPtr<AActor> actor = Utility::getGameState(this)->spawn<AActor>(actorClass, {});

	actor->FinishSpawning(GetActorTransform());

	Destroy();
}
