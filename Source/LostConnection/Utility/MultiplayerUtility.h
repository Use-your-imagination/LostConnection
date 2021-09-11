// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LOSTCONNECTION_API MultiplayerUtility
{
public:
	MultiplayerUtility() = default;

	~MultiplayerUtility() = default;

public:
	static void runOnServerReliable(UObject* caller, const FName& methodName);

	static void runOnServerUnreliable(UObject* caller, const FName& methodName);
};
