#include "SecondAbilityCast.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void ISecondAbilityCast::callCastSecondAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<UObject>(this), caster->getSecondAbility());
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
