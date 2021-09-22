#include "ThirdAbility.h"

void IThirdAbility::thirdAbility()
{
	this->thirdAbilityVisual();

	IThirdAbility::Execute_thirdAbilityEventVisual(Cast<UObject>(this));
}
