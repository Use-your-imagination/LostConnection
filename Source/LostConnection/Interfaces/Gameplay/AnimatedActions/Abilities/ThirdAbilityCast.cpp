#include "ThirdAbilityCast.h"

#include "Utility/MultiplayerUtility.h"

void IThirdAbilityCast::callCastThirdAbilityEventVisual()
{
	IThirdAbilityCast::Execute_castThirdAbilityEventVisual(Cast<UObject>(this));
}

void IThirdAbilityCast::castThirdAbilityVisual()
{
	PURE_VIRTUAL(IThirdAbilityCast::castThirdAbilityVisual);
}

void IThirdAbilityCast::castThirdAbility()
{
	if (this->checkThirdAbilityCast())
	{
		UObject* caster = Cast<UObject>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castThirdAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastThirdAbilityEventVisual");
	}
}
