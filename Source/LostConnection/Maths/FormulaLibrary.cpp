// Copyright (c) 2022 Use Your Imagination

#include "FormulaLibrary.h"

#include "Algo/Accumulate.h"

float UFormulaLibrary::standardFormula(float base, float added, const TArray<float>& increaseCoefficients, const TArray<float>& moreCoefficients, float additional)
{
	return (base + added) *
		Algo::Accumulate(increaseCoefficients, 1.0f) *
		Algo::Accumulate(moreCoefficients, 1.0f, [](float currentValue, float nextValue) { return currentValue * (1.0f + nextValue); }) +
		additional;
}
