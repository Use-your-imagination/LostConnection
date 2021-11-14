#pragma once

#include "CoreMinimal.h"

class LOSTCONNECTION_API Utility
{
public:
	Utility() = default;

	~Utility() = default;

public:
	static UWorld* getWorld();

	template<typename T>
	static bool checkChanceProc(const T& chance);
};

template<typename T>
bool Utility::checkChanceProc(const T& chance)
{
	return chance >= FMath::RandRange(static_cast<T>(0), static_cast<T>(100));
}
