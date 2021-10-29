#include "FirstAbilityCast.h"

#include "Utility/MultiplayerUtility.h"

void IFirstAbilityCast::callCastFirstAbilityEventVisual()
{
	IFirstAbilityCast::Execute_castFirstAbilityEventVisual(Cast<UObject>(this));
}

void IFirstAbilityCast::castFirstAbilityVisual()
{
	PURE_VIRTUAL(IFirstAbilityCast::castFirstAbilityVisual);
}

void IFirstAbilityCast::castFirstAbility()
{
	if (this->checkFirstAbilityCast())
	{
		UObject* caster = Cast<UObject>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castFirstAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastFirstAbilityEventVisual");
	}
}
