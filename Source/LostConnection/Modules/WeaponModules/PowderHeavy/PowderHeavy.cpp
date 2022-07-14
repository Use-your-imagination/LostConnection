// Copyright (c) 2022 Use Your Imagination

#include "PowderHeavy.h"

#include "Algo/Accumulate.h"

#include "Utility/Utility.h"

TArray<FFormatArgumentValue> UPowderHeavy::getFormatArguments() const
{
	return { Utility::toPercent(Algo::Accumulate(moduleDamage.increaseDamageCoefficients, 0.0f)) };
}

bool UPowderHeavy::applyCondition(TObjectPtr<AActor> caller) const
{
	return true;
}
