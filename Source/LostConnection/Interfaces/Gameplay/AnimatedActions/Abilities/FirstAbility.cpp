#include "FirstAbility.h"

void IFirstAbility::useFirstAbility()
{
	this->useFirstAbilityVisual();

	IFirstAbility::Execute_useFirstAbilityEventVisual(Cast<UObject>(this));
}
