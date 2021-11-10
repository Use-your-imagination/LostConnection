#include "InitializationUtility.h"

void InitializationUtility::initAbilityId(const FString& abilityClassName, abilitySlot& id)
{
	if (abilityClassName.Find(L"Passive") != INDEX_NONE)
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

UBaseStatus* InitializationUtility::createDefaultStatus(typeOfDamage type)
{
	static const TMap<typeOfDamage, UClass*> statuses =
	{
		{ typeOfDamage::physical, LoadClass<UBaseStatus>(nullptr, TEXT("Blueprint'/Game/Statuses/BP_CritStatus.BP_CritStatus'")) },
		{ typeOfDamage::cold, LoadClass<UBaseStatus>(nullptr, TEXT("Blueprint'/Game/Statuses/BP_ShatterStatus.BP_ShatterStatus'")) },
		{ typeOfDamage::nanite, LoadClass<UBaseStatus>(nullptr, TEXT("Blueprint'/Game/Statuses/BP_SwarmStatus.BP_SwarmStatus'")) },
		{ typeOfDamage::fire, LoadClass<UBaseStatus>(nullptr, TEXT("Blueprint'/Game/Statuses/BP_BurnStatus.BP_BurnStatus'")) },
		{ typeOfDamage::electricity, LoadClass<UBaseStatus>(nullptr, TEXT("Blueprint'/Game/Statuses/BP_ArcingCurrentStatus.BP_ArcingCurrentStatus'")) }
	};

	return NewObject<UBaseStatus>(nullptr, statuses[type]);
}
