// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"

#include "AI/AISpawner.h"

#include "LostConnectionGameMode.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	AISpawner& spawner = AISpawner::get();

protected:
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

public:
	ALostConnectionGameMode();

	UFUNCTION(Category = AI, Server, Reliable, BlueprintCallable)
	void spawnAI(int32 count) const;

	virtual void PostSeamlessTravel() override;

	virtual void HandleSeamlessTravelPlayer(AController*& controller) override;
};
