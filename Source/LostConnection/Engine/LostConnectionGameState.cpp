// Copyright (c) 2021 Use-your-imagination

#include "LostConnectionGameState.h"

#include "UObject/ConstructorHelpers.h"

#include "Statuses/BaseStatus.h"

ALostConnectionGameState::ALostConnectionGameState()
{
	static ConstructorHelpers::FClassFinder<UBaseStatus> crit(TEXT("/Game/Statuses/Ailments/BP_CritStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> swarm(TEXT("/Game/Statuses/Ailments/BP_SwarmStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> burn(TEXT("/Game/Statuses/Ailments/BP_BurnStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> arcingCurrent(TEXT("/Game/Statuses/Ailments/BP_ArcingCurrentStatus"));
	static ConstructorHelpers::FClassFinder<UBaseStatus> irradiation(TEXT("/Game/Statuses/Ailments/BP_IrradiationStatus"));

	statuses.Add(typeOfDamage::physical, crit.Class);
	statuses.Add(typeOfDamage::nanite, swarm.Class);
	statuses.Add(typeOfDamage::fire, burn.Class);
	statuses.Add(typeOfDamage::electricity, arcingCurrent.Class);
	statuses.Add(typeOfDamage::radiation, irradiation.Class);
}

UClass* ALostConnectionGameState::getDefaultStatus(typeOfDamage damageType) const
{
	return statuses[damageType];
}
