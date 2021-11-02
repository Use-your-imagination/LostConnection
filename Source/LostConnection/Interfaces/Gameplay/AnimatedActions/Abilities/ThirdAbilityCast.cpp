#include "ThirdAbilityCast.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IThirdAbilityCast::callCastThirdAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<UObject>(this), caster->getThirdAbility());
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
