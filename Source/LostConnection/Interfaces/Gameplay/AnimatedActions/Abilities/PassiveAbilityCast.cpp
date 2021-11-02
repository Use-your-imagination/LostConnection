#include "PassiveAbilityCast.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IPassiveAbilityCast::callCastPassiveAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<UObject>(this), caster->getPassiveAbility());
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
