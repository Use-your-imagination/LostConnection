// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Algo/AnyOf.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/LostConnectionGameState.h"
#include "Engine/LostConnectionPlayerState.h"
#include "Engine/LostConnectionPlayerController.h"
#include "Inventory/InventoryCell.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLostConnection, Display, All);

template<typename T, typename U>
auto Cast(const TScriptInterface<U>& interface);

class LOSTCONNECTION_API Utility
{
public:
	Utility() = default;

	~Utility() = default;

public:
	static TObjectPtr<ALostConnectionGameState> getGameState(const AActor* actor);

	static TObjectPtr<ALostConnectionPlayerState> getPlayerState(const APawn* pawn);

	static ALostConnectionPlayerController* getPlayerController(const APawn* pawn);

	static int32 countStatuses(const TScriptInterface<class IStatusReceiver>& target, const TSubclassOf<class UBaseStatus>& statusClass);

	static FText getTextFromFloat(float value);

	static float toPercent(float coefficient);

	static float fromPercent(float percent);

	static TSubclassOf<class ABaseDrone> findDroneClass(const TArray<const class UBaseDroneDataAsset*>& drones, const TSubclassOf<class ABaseDrone>& drone);

	static void executeOnlyOnServerFromMulticast(TObjectPtr<AActor> actor, const TFunction<void()>& function);

	static bool isYourPawn(APawn* pawn);

	static void resetDamageInflictor(class IDamageInflictor* inflictor);

	static TObjectPtr<class UBaseWeapon> createWeapon(TSubclassOf<class UBaseWeapon> weaponClass, EWeaponRarity rarity, TObjectPtr<class AInventory> inventory);

	template<typename T>
	static bool checkChanceProc(const T& chance);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(class IStatusReceiver* target);

	template<typename StatusT>
	static bool isTargetAlreadyUnderStatus(const TScriptInterface<class IStatusReceiver>& target);

	template<typename T>
	static const T& getRandomValueFromArray(const TArray<T>& values);

	template<typename T>
	static TObjectPtr<const T> findDroneAsset(const TArray<const class UBaseDroneDataAsset*>& drones);

	template<typename T>
	static void processCooldown(TObjectPtr<T> cooldownableObject, float DeltaSeconds);

	template<typename T>
	static T* setCurrentUI(const TSubclassOf<T>& widget, APawn* outer);

	template<typename FunctionT, typename... Args>
	static void executeOnOwningClient(APawn* pawn, const FunctionT& function, Args&&... args);

	template<typename InflictorT>
	static void applyDamageModules(TObjectPtr<AActor> caller, const TArray<UInventoryCell*>& modules, TObjectPtr<InflictorT> inflictor);
};

inline TObjectPtr<ALostConnectionGameState> Utility::getGameState(const AActor* actor)
{
	return actor->GetWorld()->GetGameState<ALostConnectionGameState>();
}

inline TObjectPtr<ALostConnectionPlayerState> Utility::getPlayerState(const APawn* pawn)
{
	TObjectPtr<AController> controller = pawn->GetController();

	if (controller.IsNull())
	{
		return nullptr;
	}

	return controller->GetPlayerState<ALostConnectionPlayerState>();
}

inline ALostConnectionPlayerController* Utility::getPlayerController(const APawn* pawn)
{
	return Cast<ALostConnectionPlayerController>(pawn->GetController());
}

inline float Utility::toPercent(float coefficient)
{
	return coefficient * 100.0f;
}

inline float Utility::fromPercent(float percent)
{
	return percent * 0.01f;
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

template<typename T>
TObjectPtr<const T> Utility::findDroneAsset(const TArray<const class UBaseDroneDataAsset*>& drones)
{
	TSubclassOf<class UBaseDroneDataAsset> data = T::StaticClass();

	for (const auto& i : drones)
	{
		if (TObjectPtr<const T> tem = Cast<const T>(i))
		{
			return tem;
		}
	}

	return nullptr;
}

template<typename T>
inline void Utility::processCooldown(TObjectPtr<T> cooldownableObject, float DeltaSeconds)
{
	if (TObjectPtr<class ICooldownable> tem = Cast<class ICooldownable>(cooldownableObject))
	{
		tem->processCooldown(DeltaSeconds);
	}
}

template<typename T>
T* Utility::setCurrentUI(const TSubclassOf<T>& widget, APawn* outer)
{
	ALostConnectionPlayerState* playerState = Utility::getPlayerState(outer);

	playerState->setCurrentUI(widget, outer);

	return Cast<T>(playerState->getCurrentUI());
}

template<typename FunctionT, typename... Args>
void Utility::executeOnOwningClient(APawn* pawn, const FunctionT& function, Args&&... args)
{
	check(pawn);

	AController* controller = pawn->GetController();

	if (controller && controller == UGameplayStatics::GetPlayerController(pawn, 0))
	{
		function(Forward(args)...);
	}
}

template<typename InflictorT>
void Utility::applyDamageModules(TObjectPtr<AActor> caller, const TArray<UInventoryCell*>& modules, TObjectPtr<InflictorT> inflictor)
{
	for (const auto& cell : modules)
	{
		TObjectPtr<class UBaseModule> module = cell->getItem<class UBaseModule>();

		if (IDamageModule* damageModule = Cast<IDamageModule>(module))
		{
			if (!module->applyCondition(caller))
			{
				continue;
			}

			float efficiencyCoefficient = cell->getIsEquipped() ? 1.0f : 0.5f;

			inflictor->setAddedDamage(inflictor->getAddedDamage() + damageModule->getAddedDamage() * efficiencyCoefficient);
			inflictor->appendIncreaseDamageCoefficient(damageModule->getIncreaseDamageCoefficient() * efficiencyCoefficient);
			inflictor->appendMoreDamageCoefficient(damageModule->getMoreDamageCoefficient() * efficiencyCoefficient);
			inflictor->setAdditionalDamage(inflictor->getAdditionalDamage() + damageModule->getAdditionalDamage() * efficiencyCoefficient);
		}
	}
}

template<typename T, typename U>
auto Cast(const TScriptInterface<U>& interface)
{
	if constexpr (std::is_base_of_v<UObject, T>)
	{
		return TObjectPtr<T>(Cast<T>(interface.GetObject()));
	}
	else
	{
		return TScriptInterface<T>(interface.GetObject());
	}
}
