#include "ThirdAbilityCast.h"

#include "GameFramework/Pawn.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IThirdAbilityCast::callCastThirdAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<APawn>(this), caster->getThirdAbility());
}

void IThirdAbilityCast::castThirdAbilityVisual()
{
	PURE_VIRTUAL(IThirdAbilityCast::castThirdAbilityVisual);
}

void IThirdAbilityCast::castThirdAbility()
{
	if (this->checkThirdAbilityCast())
	{
		APawn* caster = Cast<APawn>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castThirdAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastThirdAbilityEventVisual");
	}
}
