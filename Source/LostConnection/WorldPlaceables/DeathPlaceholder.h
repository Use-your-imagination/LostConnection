// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "DeathPlaceholder.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API ADeathPlaceholder : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ADeathPlaceholder() = default;

	virtual ~ADeathPlaceholder() = default;
};
