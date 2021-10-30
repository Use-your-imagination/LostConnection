#include "UltimateAbilityCast.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IUltimateAbilityCast::callCastUltimateAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<UObject>(this), caster->getPassiveAbility());
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
