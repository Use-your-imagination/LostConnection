// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"

#include "AI/AISpawnManager.h"

#include "LostConnectionGameMode.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	AISpawnManager spawnManager;

protected:
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

	virtual void BeginPlay() override;

public:
	ALostConnectionGameMode();

	UFUNCTION(Category = AI, BlueprintAuthorityOnly, BlueprintCallable)
	void initRoomAI(int32 totalCount, int32 waves);

	AISpawnManager& getSpawnManager();

	virtual void PostSeamlessTravel() override;

	virtual void HandleSeamlessTravelPlayer(AController*& controller) override;
};
