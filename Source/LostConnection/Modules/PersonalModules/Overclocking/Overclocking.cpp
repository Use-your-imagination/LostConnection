// Copyright (c) 2022 Use Your Imagination

#include "Overclocking.h"

#include "Algo/Accumulate.h"

#include "Utility/Utility.h"

TArray<FFormatArgumentValue> UOverclocking::getFormatArguments() const
{
	return { Utility::toPercent(Algo::Accumulate(moduleDamage.increaseDamageCoefficients, 0.0f)) * this->getMultiplier() };
}

bool UOverclocking::applyCondition(const TObjectPtr<AActor>& caller) const
{
	return true;
}

EDamageAffecterType UOverclocking::getDamageAffecterType() const
{
	return EDamageAffecterType::increaser;
}
