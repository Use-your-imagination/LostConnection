// Copyright (c) 2022 Use-your-imagination

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
	virtual void Tick(float DeltaTime) override;

public:
	APreConnectionPlaceholder();

	virtual ~APreConnectionPlaceholder() = default;
};
