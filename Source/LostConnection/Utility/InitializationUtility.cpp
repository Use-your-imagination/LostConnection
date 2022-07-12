// Copyright (c) 2021 Use Your Imagination

#include "InitializationUtility.h"

#include "Characters/BaseDrone.h"
#include "Engine/LostConnectionGameState.h"
#include "Utility.h"
#include "AssetLoading/LostConnectionAssetManager.h"

void InitializationUtility::initAbilityId(const FString& abilityClassName, EAbilitySlot& id)
{
	if (abilityClassName.Find("Passive") != INDEX_NONE)
	{
		id = EAbilitySlot::passiveAbility;
	}
	else if (abilityClassName.Find("First") != INDEX_NONE)
	{
		id = EAbilitySlot::firstAbility;
	}
	else if (abilityClassName.Find("Second") != INDEX_NONE)
	{
		id = EAbilitySlot::secondAbility;
	}
	else if (abilityClassName.Find("Third") != INDEX_NONE)
	{
		id = EAbilitySlot::thirdAbility;
	}
	else if (abilityClassName.Find("Ultimate") != INDEX_NONE)
	{
		id = EAbilitySlot::ultimateAbility;
	}
}

TObjectPtr<UBaseStatus> InitializationUtility::createDefaultAilment(ETypeOfDamage damageType, const TScriptInterface<IAilmentReceiver>& target)
{
	return NewObject<UBaseStatus>(target.GetObject(), ULostConnectionAssetManager::get()[damageType]);
}
