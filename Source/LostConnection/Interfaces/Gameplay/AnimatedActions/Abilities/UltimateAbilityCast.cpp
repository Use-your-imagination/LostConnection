// Copyright (c) 2021 Use Your Imagination

#include "UltimateAbilityCast.h"

#include "GameFramework/Pawn.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IUltimateAbilityCast::callCastUltimateAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<APawn>(this), caster->getUltimateAbility());
}

void IUltimateAbilityCast::castUltimateAbilityVisual()
{
	PURE_VIRTUAL(IUltimateAbilityCast::castUltimateAbilityVisual);
}

void IUltimateAbilityCast::castUltimateAbility()
{
	if (this->checkUltimateAbilityCast())
	{
		APawn* caster = Cast<APawn>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castUltimateAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastUltimateAbilityEventVisual");
	}
}
