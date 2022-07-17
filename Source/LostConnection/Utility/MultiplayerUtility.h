// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

class LOSTCONNECTION_API MultiplayerUtility
{
public:
	MultiplayerUtility() = default;

	~MultiplayerUtility() = default;

public:
	static void runOnServerReliableWithMulticast(TObjectPtr<APawn> caller, const FName& methodName);

	static void runOnServerUnreliableWithMulticast(TObjectPtr<APawn> caller, const FName& methodName);

	static void runOnServerReliable(TObjectPtr<APawn> caller, const FName& methodName);

	static void runOnServerUnreliable(TObjectPtr<APawn> caller, const FName& methodName);
};
