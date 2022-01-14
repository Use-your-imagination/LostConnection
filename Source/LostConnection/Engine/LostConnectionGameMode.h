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
	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 totalBots;

	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 remainingBots;

	UPROPERTY(Category = AI, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 remainingWaves;

	AISpawnManager spawnManager;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

public:
	ALostConnectionGameMode();

	UFUNCTION(Category = AI, Server, Reliable, BlueprintCallable)
	void initRoomAI(int32 totalCount, int32 waves);

	AISpawnManager& getSpawnManager();

	virtual void Tick(float DeltaTime) override;

	virtual void PostSeamlessTravel() override;

	virtual void HandleSeamlessTravelPlayer(AController*& controller) override;
};
