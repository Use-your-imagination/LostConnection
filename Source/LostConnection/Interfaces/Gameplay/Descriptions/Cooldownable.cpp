// Copyright (c) 2021 Use Your Imagination

#include "Cooldownable.h"

void ICooldownable::startCooldown_Implementation(float startCooldown)
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
