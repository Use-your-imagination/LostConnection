// Copyright (c) 2022 Use Your Imagination

#include "FormulaLibrary.h"

#include "Algo/Accumulate.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

float UFormulaLibrary::standardFormula(float base, float added, const TArray<float>& increaseCoefficients, const TArray<float>& moreCoefficients, float additional)
{
	return (base + added) *
		Algo::Accumulate(increaseCoefficients, 1.0f) *
		Algo::Accumulate(moreCoefficients, 1.0f, [](float currentValue, float nextValue) { return currentValue * (1.0f + nextValue); }) +
		additional;
}

float UFormulaLibrary::calculateDamageAfterResist(float base, float added, const TArray<float>& increaseCoefficients, const TArray<float>& moreCoefficients, float additional, const TScriptInterface<IDamageInflictor>& inflictor)
{
	static float resistHardcap = ULostConnectionAssetManager::get().getDefaults().getResistHardcap();
	float resist = UFormulaLibrary::standardFormula(base, added, increaseCoefficients, moreCoefficients, additional);
	float damage = inflictor->calculateTotalDamage();

	return FMath::Max(damage * resistHardcap, damage * resist);
}
