#include "PassiveAbilityCast.h"

#include "GameFramework/Pawn.h"

#include "Utility/MultiplayerUtility.h"
#include "Interfaces/Gameplay/Descriptions/Caster.h"

void IPassiveAbilityCast::callCastPassiveAbilityEventVisual()
{
	ICaster* caster = Cast<ICaster>(this);

	ICaster::Execute_castAbilityEventVisual(Cast<APawn>(this), caster->getPassiveAbility());
}

void IPassiveAbilityCast::castPassiveAbilityVisual()
{
	PURE_VIRTUAL(IPassiveAbilityCast::castPassiveAbilityVisual);
}

void IPassiveAbilityCast::castPassiveAbility()
{
	if (this->checkPassiveAbilityCast())
	{
		APawn* caster = Cast<APawn>(this);

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "castPassiveAbilityVisual");

		MultiplayerUtility::runOnServerReliableWithMulticast(caster, "callCastPassiveAbilityEventVisual");
	}
}
