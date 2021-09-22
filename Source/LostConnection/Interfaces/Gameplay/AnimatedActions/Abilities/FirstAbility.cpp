#include "FirstAbility.h"

void IFirstAbility::firstAbility()
{
	this->firstAbilityVisual();

	IFirstAbility::Execute_firstAbilityEventVisual(Cast<UObject>(this));
}
