// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "AllySelection.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAllySelection : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IAllySelection
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IAllySelection() = default;

	UFUNCTION(BlueprintNativeEvent)
	void selectFirstPlayer();

	UFUNCTION(BlueprintNativeEvent)
	void selectSecondPlayer();

	UFUNCTION(BlueprintNativeEvent)
	void selectThirdPlayer();

	UFUNCTION(BlueprintNativeEvent)
	void selectFourthPlayer();
};
