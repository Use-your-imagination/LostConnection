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

bool ICooldownable::isUsable() const
{
	return const_cast<ICooldownable*>(this)->getCurrentCooldown() == 0.0f;
}

void ICooldownable::resetCooldown()
{
	this->getCurrentCooldown() = 0.0f;
}
