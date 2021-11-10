#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Statuses/BaseStatus.h"

class LOSTCONNECTION_API InitializationUtility
{
public:
	InitializationUtility() = default;

	~InitializationUtility() = default;

public:
	static void initAbilityId(const FString& abilityClassName, abilitySlot& id);

	static UBaseStatus* createDefaultStatus(typeOfDamage type);
};
