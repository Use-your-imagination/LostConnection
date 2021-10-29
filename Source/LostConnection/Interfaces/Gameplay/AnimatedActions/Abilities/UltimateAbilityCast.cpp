#include "UltimateAbilityCast.h"

#include "Utility/MultiplayerUtility.h"

void IUltimateAbilityCast::callCastUltimateAbilityEventVisual()
{
	IUltimateAbilityCast::Execute_castUltimateAbilityEventVisual(Cast<UObject>(this));
}

void IUltimateAbilityCast::castUltimateAbilityVisual()
{
	PURE_VIRTUAL(IUltimateAbilityCast::castUltimateAbilityVisual);
}

void IUltimateAbilityCast::castUltimateAbility()
{
	if (this->checkUltimateAbilityCast())
	{
		UObject* caster = Cast<UObject>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castUltimateAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastUltimateAbilityEventVisual");
	}
}
