// Copyright (c) 2022 Use Your Imagination

#include "Overclocking.h"

#include "Utility/Utility.h"

TArray<FFormatArgumentValue> UOverclocking::getFormatArguments() const
{
	return { Utility::toPercent(this->getIncreaseDamageCoefficient()) };
}

bool UOverclocking::applyCondition(TObjectPtr<AActor> caller) const
{
	return true;
}
