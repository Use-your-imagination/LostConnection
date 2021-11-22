// Copyright (c) 2021 Use-your-imagination

#include "Death.h"

void IDeath::death()
{
	this->deathVisual();

	IDeath::Execute_deathEventVisual(Cast<UObject>(this));
}
