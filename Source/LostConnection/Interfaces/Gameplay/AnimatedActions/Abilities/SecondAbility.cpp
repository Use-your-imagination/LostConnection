#include "SecondAbility.h"

void ISecondAbility::useSecondAbility()
{
	this->useSecondAbilityVisual();

	ISecondAbility::Execute_useSecondAbilityEventVisual(Cast<UObject>(this));
}
