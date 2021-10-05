#include "PassiveAbility.h"

void IPassiveAbility::usePassiveAbility()
{
	this->usePassiveAbilityVisual();

	IPassiveAbility::Execute_usePassiveAbilityEventVisual(Cast<UObject>(this));
}
