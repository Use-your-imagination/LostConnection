// Copyright (c) 2022 Use Your Imagination

#include "IncreaseOutputDamageModule.h"

#include "Utility/Utility.h"

bool UIncreaseOutputDamageModule::applyCondition(TObjectPtr<AActor> caller) const
{
	return true;
}

float UIncreaseOutputDamageModule::getAddedDamage() const
{
	return 0.0f;
}

float UIncreaseOutputDamageModule::getIncreaseDamageCoefficient() const
{
	return 0.0f;
}

float UIncreaseOutputDamageModule::getMoreDamageCoefficient() const
{
	return moreDamageCoefficient;
}

float UIncreaseOutputDamageModule::getAdditionalDamage() const
{
	return 0.0f;
}
