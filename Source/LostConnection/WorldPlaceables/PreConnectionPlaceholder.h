// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "PreConnectionPlaceholder.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API APreConnectionPlaceholder : public APawn
{
	GENERATED_BODY()

private:
	bool isAlreadySendRespawnRequest;

protected:
	UFUNCTION(Client, Reliable)
	virtual void Tick(float DeltaSeconds) override;

public:
	APreConnectionPlaceholder();

	~APreConnectionPlaceholder() = default;
};
