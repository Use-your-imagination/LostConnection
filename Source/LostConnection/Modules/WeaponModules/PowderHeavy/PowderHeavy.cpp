// Copyright (c) 2022 Use Your Imagination

#include "PowderHeavy.h"

#include "Utility/Utility.h"

TArray<FFormatArgumentValue> UPowderHeavy::getFormatArguments() const
{
	return { Utility::toPercent(this->getIncreaseDamageCoefficient()) };
}

bool UPowderHeavy::applyCondition(TObjectPtr<AActor> caller) const
{
	return true;
}
