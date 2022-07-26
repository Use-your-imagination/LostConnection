// Copyright (c) 2022 Use Your Imagination

#include "FormulaLibrary.h"

#include "Algo/Accumulate.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Interfaces/Gameplay/Descriptions/DamageAffecter.h"

float UFormulaLibrary::standardFormulaArguments(float base, float added, const TArray<float>& increaseCoefficients, const TArray<float>& moreCoefficients, float additional)
{
	static float resistHardcap = ULostConnectionAssetManager::get().getDefaults().getResistHardcap();
	float damage = (base + added) *
		Algo::Accumulate(increaseCoefficients, 1.0f) *
		Algo::Accumulate(moreCoefficients, 1.0f, [](float currentValue, float nextValue) { return currentValue * (1.0f + nextValue); }) +
		additional;

	// TODO: resist
	// return FMath::Max(damage * resistHardcap, damage * resist);

	return damage;
}

float UFormulaLibrary::standardFormulaDamage(const FDamageStructure& damage)
{
	return UFormulaLibrary::standardFormulaArguments
	(
		damage.baseDamage,
		damage.addedDamage,
		damage.increaseDamageCoefficients,
		damage.moreDamageCoefficients,
		damage.additionalDamage
	);
}
