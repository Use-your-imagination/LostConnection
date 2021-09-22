// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "MovementActions.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMovementActions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IMovementActions
{
	GENERATED_BODY()

public:
	IMovementActions() = default;

	UFUNCTION(BlueprintNativeEvent)
	void pressSprintAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseSprintAction();

	UFUNCTION(BlueprintNativeEvent)
	void pressCrouchAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseCrouchAction();

	UFUNCTION(BlueprintNativeEvent)
	void pressJumpAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseJumpAction();
};
