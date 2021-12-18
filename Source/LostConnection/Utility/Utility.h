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

	static SIZE_T countStatuses(const class IStatusReceiver* target, const TSubclassOf<class UBaseStatus>& statusClass);

	static FText getFTextFromFloat(float value);

	static float toPercent(float coefficient);

	static float fromPercent(float percent);

	static TSubclassOf<class ABaseDrone> findDrone(const TArray<const class UBaseDroneDataAsset*>& drones, const TSubclassOf<class ABaseDrone>& drone);

	template<typename T>
	static bool checkChanceProc(const T& chance);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(class IStatusReceiver* target);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(const TScriptInterface<class IStatusReceiver>& target);

	template<typename T>
	static const T& getRandomValueFromArray(const TArray<T>& values);
};

inline float Utility::toPercent(float coefficient)
{
	return coefficient * 100.0f;
}

inline float Utility::fromPercent(float percent)
{
	return percent / 100.0f;
}

template<typename T>
bool Utility::checkChanceProc(const T& chance)
{
	return chance >= FMath::RandRange(StaticCast<T>(1), StaticCast<T>(100));
}

template<typename StatusT>
bool Utility::isTargetAlreadyUnderStatus(class IStatusReceiver* target)
{
	const TArray<class UBaseStatus*>& statuses = target->getStatuses();

	return Algo::AnyOf(statuses, [](const UBaseStatus* status) { return StaticCast<bool>(Cast<StatusT>(status)); });
}

template<typename StatusT>
bool Utility::isTargetAlreadyUnderStatus(const TScriptInterface<class IStatusReceiver>& target)
{
	return Utility::isTargetAlreadyUnderStatus<StatusT>(StaticCast<class IStatusReceiver*>(target.GetInterface()));
}

template<typename T>
const T& Utility::getRandomValueFromArray(const TArray<T>& values)
{
	check(values.Num() != 0);

	return values[FMath::RandRange(0, values.Num() - 1)];
}
