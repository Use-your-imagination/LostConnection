// Copyright (c) 2021 Use-your-imagination

#include "InitializationUtility.h"

#include "Characters/BaseDrone.h"
#include "Engine/LostConnectionGameState.h"
#include "Interfaces/Gameplay/Descriptions/Derived/AilmentReceiver.h"
#include "Utility.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void InitializationUtility::initAbilityId(const FString& abilityClassName, abilitySlot& id)
{
	if (abilityClassName.Find("Passive") != INDEX_NONE)
	{
		id = abilitySlot::passiveAbility;
	}
	else if (abilityClassName.Find("First") != INDEX_NONE)
	{
		id = abilitySlot::firstAbility;
	}
	else if (abilityClassName.Find("Second") != INDEX_NONE)
	{
		id = abilitySlot::secondAbility;
	}
	else if (abilityClassName.Find("Third") != INDEX_NONE)
	{
		id = abilitySlot::thirdAbility;
	}
	else if (abilityClassName.Find("Ultimate") != INDEX_NONE)
	{
		id = abilitySlot::ultimateAbility;
	}
}

UBaseStatus* InitializationUtility::createDefaultStatus(typeOfDamage damageType, IAilmentReceiver* target)
{
	return NewObject<UBaseStatus>(target->_getUObject(), ULostConnectionAssetManager::get()[damageType]);
}
