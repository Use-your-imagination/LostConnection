// Copyright (c) 2021 Use-your-imagination

#include "SecondAbilityCast.h"

#include "GameFramework/Pawn.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void ISecondAbilityCast::callCastSecondAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<APawn>(this), caster->getSecondAbility());
}

void ISecondAbilityCast::castSecondAbilityVisual()
{
	PURE_VIRTUAL(ISecondAbilityCast::castSecondAbilityVisual);
}

void ISecondAbilityCast::castSecondAbility()
{
	if (this->checkSecondAbilityCast())
	{
		APawn* caster = Cast<APawn>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castSecondAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastSecondAbilityEventVisual");
	}
}
