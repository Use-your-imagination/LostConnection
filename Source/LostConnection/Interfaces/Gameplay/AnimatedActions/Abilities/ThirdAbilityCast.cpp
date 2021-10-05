#include "ThirdAbilityCast.h"

void IThirdAbilityCast::castThirdAbility()
{
	this->castThirdAbilityVisual();

	IThirdAbilityCast::Execute_castThirdAbilityEventVisual(Cast<UObject>(this));
}
