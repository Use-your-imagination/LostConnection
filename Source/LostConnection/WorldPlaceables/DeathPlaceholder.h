// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerInput.h"

#include "DeathPlaceholder.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API ADeathPlaceholder : public APawn
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void checkRespawn();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	ADeathPlaceholder() = default;

	virtual ~ADeathPlaceholder() = default;
};
