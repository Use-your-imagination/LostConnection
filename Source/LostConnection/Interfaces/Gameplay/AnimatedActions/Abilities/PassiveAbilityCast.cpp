#include "PassiveAbilityCast.h"

#include "Utility/MultiplayerUtility.h"

void IPassiveAbilityCast::callCastPassiveAbilityEventVisual()
{
	IPassiveAbilityCast::Execute_castPassiveAbilityEventVisual(Cast<UObject>(this));
}

void IPassiveAbilityCast::castPassiveAbilityVisual()
{
	PURE_VIRTUAL(IPassiveAbilityCast::castPassiveAbilityVisual);
}

void IPassiveAbilityCast::castPassiveAbility()
{
	if (this->checkPassiveAbilityCast())
	{
		UObject* caster = Cast<UObject>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castPassiveAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastPassiveAbilityEventVisual");
	}
}
