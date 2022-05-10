// Copyright (c) 2021 Use Your Imagination

#include "FirstAbilityCast.h"

#include "GameFramework/Pawn.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IFirstAbilityCast::callCastFirstAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<APawn>(this), caster->getFirstAbility());
}

void IFirstAbilityCast::castFirstAbilityVisual()
{
	PURE_VIRTUAL(IFirstAbilityCast::castFirstAbilityVisual);
}

void IFirstAbilityCast::castFirstAbility()
{
	if (this->checkFirstAbilityCast())
	{
		APawn* caster = Cast<APawn>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castFirstAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastFirstAbilityEventVisual");
	}
}
