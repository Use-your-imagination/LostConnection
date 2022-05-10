// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Statuses/BaseStatus.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

class LOSTCONNECTION_API InitializationUtility
{
public:
	InitializationUtility() = default;

	~InitializationUtility() = default;

public:
	static void initAbilityId(const FString& abilityClassName, EAbilitySlot& id);

	static UBaseStatus* createDefaultAilment(ETypeOfDamage damageType, IAilmentReceiver* target);
};
