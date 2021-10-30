#pragma once

#include "CoreMinimal.h"

class LOSTCONNECTION_API MultiplayerUtility
{
public:
	MultiplayerUtility() = default;

	~MultiplayerUtility() = default;

public:
	static void runOnServerReliableWithMulticast(UObject* caller, const FName& methodName);

	static void runOnServerUnreliableWithMulticast(UObject* caller, const FName& methodName);

	static void runOnServerReliable(UObject* caller, const FName& methodName);

	static void runOnServerUnreliable(UObject* caller, const FName& methodName);
};
