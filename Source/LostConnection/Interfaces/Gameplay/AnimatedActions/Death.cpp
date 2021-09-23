#include "Death.h"

void IDeath::death()
{
	this->deathVisual();

	IDeath::Execute_deathEventVisual(Cast<UObject>(this));
}
