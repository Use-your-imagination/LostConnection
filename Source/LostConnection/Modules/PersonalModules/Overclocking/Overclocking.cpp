// Copyright (c) 2022 Use Your Imagination

#include "Overclocking.h"

#include "Utility/Utility.h"

bool UOverclocking::applyCondition(TObjectPtr<AActor> caller) const
{
	return true;
}

float UOverclocking::getAddedDamage() const
{
	return 0.0f;
}

float UOverclocking::getIncreaseDamageCoefficient() const
{
	return 0.0f;
}

float UOverclocking::getMoreDamageCoefficient() const
{
	return moreDamageCoefficient;
}

float UOverclocking::getAdditionalDamage() const
{
	return 0.0f;
}
