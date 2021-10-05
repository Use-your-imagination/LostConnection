#include "ThirdAbility.h"

void IThirdAbility::useThirdAbility()
{
	this->useThirdAbilityVisual();

	IThirdAbility::Execute_useThirdAbilityEventVisual(Cast<UObject>(this));
}
