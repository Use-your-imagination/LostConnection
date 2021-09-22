#include "UltimateAbility.h"

void IUltimateAbility::ultimateAbility()
{
	this->ultimateAbilityVisual();

	IUltimateAbility::Execute_ultimateAbilityEventVisual(Cast<UObject>(this));
}
