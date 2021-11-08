#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

class LOSTCONNECTION_API InitUtility
{
public:
	InitUtility() = default;

	~InitUtility() = default;

public:
	static void initAbilityId(const FString& abilityClassName, abilitySlot& id);
};
