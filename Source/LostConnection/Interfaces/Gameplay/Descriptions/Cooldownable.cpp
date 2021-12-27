// Copyright (c) 2021 Use-your-imagination

#include "Cooldownable.h"

void ICooldownable::startCooldown(float startCooldown)
{
	if (startCooldown)
	{
		this->getCurrentCooldown() = startCooldown;
	}
	else
	{
		this->getCurrentCooldown() = this->getCooldown();
	}
}

void ICooldownable::processCooldown(float DeltaTime)
{
	float& currentCooldown = this->getCurrentCooldown();

	if (currentCooldown)
	{
		currentCooldown = FMath::Max(0.0f, currentCooldown - DeltaTime);
	}
}

void ICooldownable::resetCooldown()
{
	this->getCurrentCooldown() = 0.0f;
}
