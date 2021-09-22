#include "SecondAbility.h"

void ISecondAbility::secondAbility()
{
	this->secondAbilityVisual();

	ISecondAbility::Execute_secondAbilityEventVisual(Cast<UObject>(this));
}
