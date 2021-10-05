#include "UltimateAbility.h"

void IUltimateAbility::useUltimateAbility()
{
	this->useUltimateAbilityVisual();

	IUltimateAbility::Execute_useUltimateAbilityEventVisual(Cast<UObject>(this));
}
