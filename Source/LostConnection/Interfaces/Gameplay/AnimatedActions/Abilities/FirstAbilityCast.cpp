#include "FirstAbilityCast.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IFirstAbilityCast::callCastFirstAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<UObject>(this), caster->getPassiveAbility());
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
