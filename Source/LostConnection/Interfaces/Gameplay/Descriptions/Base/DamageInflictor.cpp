// Copyright (c) 2021 Use Your Imagination

#include "DamageInflictor.h"

#include "Algo/Accumulate.h"

float IDamageInflictor::calculateTotalDamage() const
{
	TArray<float> increasedDamageCoefficients = this->getIncreaseDamageCoefficients();
	TArray<float> moreDamageCoefficients = this->getMoreDamageCoefficients();

	return (this->getBaseDamage() + this->getAddedDamage()) *
		Algo::Accumulate(increasedDamageCoefficients, 1.0f) *
		Algo::Accumulate(moreDamageCoefficients, 1.0f, [](float currentValue, float nextValue) { return currentValue * (1.0f + nextValue); }) +
		this->getAdditionalDamage();
}
