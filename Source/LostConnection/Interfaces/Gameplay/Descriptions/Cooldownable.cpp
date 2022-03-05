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

	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString::Printf(L"cooldown: %f, currentCooldown: %f, currentCooldownReference: %f", this->getCooldown(), this->getCurrentCooldownReference(), this->getCurrentCooldown()));
}

void ICooldownable::resetCooldown()
{
	this->getCurrentCooldownReference() = 0.0f;
}
