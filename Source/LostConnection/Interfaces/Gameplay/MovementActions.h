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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IMovementActions() = default;

	UFUNCTION(BlueprintNativeEvent)
	void runAction();

	UFUNCTION(BlueprintNativeEvent)
	void sprintAction();

	UFUNCTION(BlueprintNativeEvent)
	void crouchAction();

	UFUNCTION(BlueprintNativeEvent)
	void jumpAction();
};
