// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"

#include "LostConnectionGameMode.generated.h"

UCLASS()
class LOSTCONNECTION_API ALostConnectionGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;

	virtual void BeginPlay() override;

public:
	ALostConnectionGameMode();

	void PostSeamlessTravel() override;

	void HandleSeamlessTravelPlayer(AController*& C) override;
};
