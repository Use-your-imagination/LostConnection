#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

class LOSTCONNECTION_API MultiplayerUtility
{
public:
	MultiplayerUtility() = default;

	~MultiplayerUtility() = default;

public:
	static void runOnServerReliableWithMulticast(APawn* caller, const FName& methodName);

	static void runOnServerUnreliableWithMulticast(APawn* caller, const FName& methodName);

	static void runOnServerReliable(APawn* caller, const FName& methodName);

	static void runOnServerUnreliable(APawn* caller, const FName& methodName);
};
