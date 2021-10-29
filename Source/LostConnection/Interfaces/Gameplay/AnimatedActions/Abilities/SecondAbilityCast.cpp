#include "SecondAbilityCast.h"

#include "Utility/MultiplayerUtility.h"

void ISecondAbilityCast::callCastSecondAbilityEventVisual()
{
	ISecondAbilityCast::Execute_castSecondAbilityEventVisual(Cast<UObject>(this));
}

void ISecondAbilityCast::castSecondAbilityVisual()
{
	PURE_VIRTUAL(ISecondAbilityCast::castSecondAbilityVisual);
}

void ISecondAbilityCast::castSecondAbility()
{
	if (this->checkSecondAbilityCast())
	{
		UObject* caster = Cast<UObject>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castSecondAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastSecondAbilityEventVisual");
	}
}
