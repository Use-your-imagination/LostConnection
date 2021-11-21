#pragma once

#include "CoreMinimal.h"

#include "Algo/AnyOf.h"

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

	static SIZE_T countStatuses(const class IStatusReceiver* target, UClass* statusStaticClass);

	template<typename T>
	static bool checkChanceProc(const T& chance);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(class IStatusReceiver* target);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(const TScriptInterface<class IStatusReceiver>& target);
};

template<typename T>
bool Utility::checkChanceProc(const T& chance)
{
	return chance >= FMath::RandRange(static_cast<T>(1), static_cast<T>(100));
}

template<typename StatusT>
bool Utility::isTargetAlreadyUnderStatus(class IStatusReceiver* target)
{
	const TArray<class UBaseStatus*>& statuses = target->getStatuses();

	return Algo::AnyOf(statuses, [](const UBaseStatus* status) { return static_cast<bool>(Cast<StatusT>(status)); });
}

template<typename StatusT>
bool Utility::isTargetAlreadyUnderStatus(const TScriptInterface<class IStatusReceiver>& target)
{
	return Utility::isTargetAlreadyUnderStatus<StatusT>(static_cast<class IStatusReceiver*>(target.GetInterface()));
}
