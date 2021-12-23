// Copyright (c) 2021 Use-your-imagination

#include "Cooldownable.h"

void ICooldownable::startCooldown()
{
	this->getCurrentCooldown() = this->getCooldown();
}

void ICooldownable::processCooldown(float DeltaTime)
{
	float& currentCooldown = this->getCurrentCooldown();

	if (currentCooldown != 0.0f)
	{
		currentCooldown = FMath::Max(0.0f, currentCooldown - DeltaTime);
	}
}

void ICooldownable::resetCooldown()
{
	this->getCurrentCooldown() = 0.0f;
}
