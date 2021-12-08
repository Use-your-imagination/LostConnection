// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "AI/AISpawner.h"

#include "LostConnectionGameMode.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	AISpawner& spawner = AISpawner::get();

protected:
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

public:
	ALostConnectionGameMode();
};
