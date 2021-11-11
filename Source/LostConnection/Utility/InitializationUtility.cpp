#include "InitializationUtility.h"

#include "Characters/BaseDrone.h"
#include "Engine/LostConnectionGameState.h"
#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

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

UBaseStatus* InitializationUtility::createDefaultStatus(typeOfDamage type, IStatusReceiver* target)
{
	static ALostConnectionGameState* gameState = ABaseDrone::globalPlayerPtr->GetWorld()->GetGameState<ALostConnectionGameState>();

	static const TMap<typeOfDamage, UClass*> statuses =
	{
		{ typeOfDamage::physical, LoadClass<UBaseStatus>(gameState, TEXT("Blueprint'/Game/Statuses/BP_CritStatus.BP_CritStatus_C'")) },
		{ typeOfDamage::cold, LoadClass<UBaseStatus>(gameState, TEXT("Blueprint'/Game/Statuses/BP_ShatterStatus.BP_ShatterStatus_C'")) },
		{ typeOfDamage::nanite, LoadClass<UBaseStatus>(gameState, TEXT("Blueprint'/Game/Statuses/BP_SwarmStatus.BP_SwarmStatus_C'")) },
		{ typeOfDamage::fire, LoadClass<UBaseStatus>(gameState, TEXT("Blueprint'/Game/Statuses/BP_BurnStatus.BP_BurnStatus_C'")) },
		{ typeOfDamage::electricity, LoadClass<UBaseStatus>(gameState, TEXT("Blueprint'/Game/Statuses/BP_ArcingCurrentStatus.BP_ArcingCurrentStatus_C'")) }
	};

	return NewObject<UBaseStatus>(target->_getUObject(), statuses[type]);
}
