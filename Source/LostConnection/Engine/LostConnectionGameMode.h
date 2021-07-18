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

protected:
	void BeginPlay() override;

public:
	ALostConnectionGameMode();
};
