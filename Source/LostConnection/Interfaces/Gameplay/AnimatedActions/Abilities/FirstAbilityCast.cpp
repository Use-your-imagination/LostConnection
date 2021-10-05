#include "FirstAbilityCast.h"

void IFirstAbilityCast::castFirstAbility()
{
	this->castFirstAbilityVisual();

	IFirstAbilityCast::Execute_castFirstAbilityEventVisual(Cast<UObject>(this));
}
