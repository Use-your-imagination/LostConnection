#include "PassiveAbility.h"

void IPassiveAbility::passiveAbility()
{
	this->passiveAbilityVisual();

	IPassiveAbility::Execute_passiveAbilityEventVisual(Cast<UObject>(this));
}
