#include "InitUtility.h"

void InitUtility::initAbilityId(const FString& abilityClassName, abilitySlot& id)
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
