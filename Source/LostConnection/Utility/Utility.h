#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"

#include "Engine/LostConnectionGameState.h"
#include "Engine/LostConnectionPlayerState.h"

class LOSTCONNECTION_API Utility
{
public:
	Utility() = default;

	~Utility() = default;

public:
	static ALostConnectionGameState* getGameState(APawn* pawn);

	static ALostConnectionPlayerState* getPlayerState(APawn* pawn);

	template<typename T>
	static bool checkChanceProc(const T& chance);
};

template<typename T>
bool Utility::checkChanceProc(const T& chance)
{
	return chance >= FMath::RandRange(static_cast<T>(0), static_cast<T>(100));
}
