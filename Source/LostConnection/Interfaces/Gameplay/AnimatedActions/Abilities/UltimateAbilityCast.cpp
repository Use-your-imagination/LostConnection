#include "UltimateAbilityCast.h"

void IUltimateAbilityCast::castUltimateAbility()
{
	this->castUltimateAbilityVisual();

	IUltimateAbilityCast::Execute_castUltimateAbilityEventVisual(Cast<UObject>(this));
}
