// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "ShotThrough.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UShotThrough : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOSTCONNECTION_API IShotThrough
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IShotThrough() = default;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float getFlatDamageReduction() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float getPercentageDamageReduction() const;
};
