#include "LostConnectionGameState.h"

#include "UObject/ConstructorHelpers.h"

#include "Statuses/BaseStatus.h"

ALostConnectionGameState::ALostConnectionGameState()
{
	static ConstructorHelpers::FClassFinder<UBaseStatus> crit(TEXT("/Game/Statuses/BP_CritStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> shatter(TEXT("/Game/Statuses/BP_ShatterStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> swarm(TEXT("/Game/Statuses/BP_SwarmStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> burn(TEXT("/Game/Statuses/BP_BurnStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> arcingCurrent(TEXT("/Game/Statuses/BP_ArcingCurrentStatus"));

	statuses.Add(typeOfDamage::physical, crit.Class);
	statuses.Add(typeOfDamage::cold, shatter.Class);
	statuses.Add(typeOfDamage::nanite, swarm.Class);
	statuses.Add(typeOfDamage::fire, burn.Class);
	statuses.Add(typeOfDamage::electricity, arcingCurrent.Class);
}

UClass* ALostConnectionGameState::getDefaultStatus(typeOfDamage damageType) const
{
	return statuses[damageType];
}
