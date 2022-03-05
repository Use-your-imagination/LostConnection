// Copyright (c) 2021 Use-your-imagination

#include "Cooldownable.h"

void ICooldownable::startCooldown(float startCooldown)
{
	if (startCooldown >= 0.0f)
	{
		this->getCurrentCooldownReference() = startCooldown;
	}
	else
	{
		this->getCurrentCooldownReference() = this->getCooldown();
	}
}

void ICooldownable::resetCooldown()
{
	this->getCurrentCooldownReference() = 0.0f;
}
