// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "LostConnectionGameMode.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UClass* defaultAI;

	UPROPERTY(Category = "Debug|Spawn", EditAnywhere)
	FVector location;

	UPROPERTY(Category = "Debug|Spawn", EditAnywhere, Meta = (DisplayAfter = "location"))
	uint16 count;

protected:
	virtual void BeginPlay() override;

	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

public:
	ALostConnectionGameMode();

	UFUNCTION(Category = "Debug|Spawn", Server, Reliable, CallInEditor, Meta = (DisplayAfter = "count"))
	void spawnAI() const;
};
