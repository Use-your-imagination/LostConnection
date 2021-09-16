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

#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = "Debug|Spawn", EditAnywhere)
	FVector location;

	UPROPERTY(Category = "Debug|Spawn", EditAnywhere, Meta = (DisplayAfter = "location"))
	uint16 count;
#endif // WITH_EDITOR_ONLY_DATA

protected:
	void BeginPlay() override;

public:
	ALostConnectionGameMode();

#if WITH_EDITORONLY_DATA
	UFUNCTION(Category = "Debug|Spawn", Server, Reliable, CallInEditor, Meta = (DisplayAfter = "count"))
	void spawnAI() const;
#endif // WITH_EDITOR_ONLY_DATA
};
