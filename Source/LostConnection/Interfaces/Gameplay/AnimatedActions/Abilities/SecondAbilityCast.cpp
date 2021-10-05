#include "SecondAbilityCast.h"

void ISecondAbilityCast::castSecondAbility()
{
	this->castSecondAbilityVisual();

	ISecondAbilityCast::Execute_castSecondAbilityEventVisual(Cast<UObject>(this));
}
