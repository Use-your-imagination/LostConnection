// Copyright (c) 2021 Use-your-imagination

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

	static SIZE_T countStatuses(const class IAilmentReceiver* target, UClass* statusStaticClass);

	template<typename T>
	static bool checkChanceProc(const T& chance);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(class IAilmentReceiver* target);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(const TScriptInterface<class IAilmentReceiver>& target);
};

template<typename T>
bool Utility::checkChanceProc(const T& chance)
{
	return chance >= FMath::RandRange(StaticCast<T>(1), StaticCast<T>(100));
}

template<typename StatusT>
bool Utility::isTargetAlreadyUnderStatus(class IAilmentReceiver* target)
{
	const TArray<class UBaseStatus*>& statuses = target->getStatuses();

	return Algo::AnyOf(statuses, [](const UBaseStatus* status) { return StaticCast<bool>(Cast<StatusT>(status)); });
}

template<typename StatusT>
bool Utility::isTargetAlreadyUnderStatus(const TScriptInterface<class IAilmentReceiver>& target)
{
	return Utility::isTargetAlreadyUnderStatus<StatusT>(StaticCast<class IAilmentReceiver*>(target.GetInterface()));
}
