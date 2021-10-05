#include "PassiveAbilityCast.h"

void IPassiveAbilityCast::castPassiveAbility()
{
	this->castPassiveAbilityVisual();

	IPassiveAbilityCast::Execute_castPassiveAbilityEventVisual(Cast<UObject>(this));
}
