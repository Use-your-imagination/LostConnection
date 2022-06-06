// Copyright (c) 2022 Use Your Imagination

#include "LootCreator.h"

#include "Kismet/KismetMathLibrary.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Utility/Utility.h"
#include "Characters/BaseDrone.h"

template<typename T, typename LootFunctionT, typename RangeEnumT>
bool LootCreator::createRandomLoot
(
	int32 lootPoints,
	TObjectPtr<AInventory> playerInventory,
	const TArray<LootFunctionT>& lootFunctions,
	const TArray<TSubclassOf<T>>& classes,
	const TFunction<RangeEnumT(LootFunctionT)>& getRangeEnum,
	TSubclassOf<T>& classToCreate,
	RangeEnumT& resultRange
) const
{
	TArray<TTuple<float, float, RangeEnumT>> ranges;

	ranges.Reserve(lootFunctions.Num());

	for (LootFunctionT lootFunction : lootFunctions)
	{
		float chance = lootFunction->calculateLootChance(lootPoints);
		RangeEnumT rarity = getRangeEnum(lootFunction);

		if (ranges.Num())
		{
			float rangeEnd = ranges.Last().Get<1>();

			ranges.Emplace(rangeEnd, rangeEnd + chance, rarity);
		}
		else
		{
			ranges.Emplace(0.0f, chance, rarity);
		}
	}

	float chance = FMath::FRandRange(0.0f, 100.0f);
	TTuple<float, float, RangeEnumT>* it = ranges.FindByPredicate([&chance](const TTuple<float, float, RangeEnumT>& range)
		{
			const float& begin = range.Get<0>();
			const float& end = range.Get<1>();

			return begin != end && UKismetMathLibrary::InRange_FloatFloat(chance, begin, end);
		}
	);

	if (it)
	{
		classToCreate = Utility::getRandomValueFromArray(classes);

		resultRange = it->Get<RangeEnumT>();
	}

	return StaticCast<bool>(it);
}

LootCreator::LootCreator() :
	weaponsGetter([](TObjectPtr<UBaseWeaponsLootFunction> function) { return function->getWeaponRarity(); }),
	modulesGetter([](TObjectPtr<UBaseModulesLootFunction> function) { return function->getModuleQuality(); }),
	weaponModulesGetter([](TObjectPtr<UBaseWeaponModulesLootFunction> function) { return function->getModuleQuality(); })
{

}

void LootCreator::createRandomWeapon(int32 lootPoints, TObjectPtr<AInventory> playerInventory, const TArray<TObjectPtr<UBaseWeaponsLootFunction>>& lootFunctions) const
{
	static const TArray<TSubclassOf<UBaseWeapon>>& weapons = ULostConnectionAssetManager::get().getLoot().getWeapons();
	TSubclassOf<UBaseWeapon> weaponClass;
	EWeaponRarity rarity;

	if (!this->createRandomLoot<UBaseWeapon, TObjectPtr<UBaseWeaponsLootFunction>, EWeaponRarity>(lootPoints, playerInventory, lootFunctions, weapons, weaponsGetter, weaponClass, rarity))
	{
		return;
	}

	TObjectPtr<UBaseWeapon> weapon = NewObject<UBaseWeapon>(playerInventory, weaponClass);

	playerInventory->addUnequippedWeapon(weapon);

	if (TObjectPtr<ABaseDrone> drone = playerInventory->getPlayerState()->GetPawn<ABaseDrone>())
	{
		weapon->setOwner(drone);

		weapon->updateTimeBetweenShots();
	}
}

void LootCreator::createRandomModule(int32 lootPoints, TObjectPtr<AInventory> playerInventory, const TArray<TObjectPtr<UBaseModulesLootFunction>>& lootFunctions) const
{
	static const TMap<TSubclassOf<UBasePersonalModule>, TSubclassOf<UBasePersonalModule>>& modules = ULostConnectionAssetManager::get().getLoot().getPersonalModules();
	static TArray<TSubclassOf<UBasePersonalModule>> personalModules = []()
	{
		TArray<TSubclassOf<UBasePersonalModule>> result;

		modules.GenerateKeyArray(result);

		return result;
	}();
	TSubclassOf<UBasePersonalModule> personalClass;
	EModuleQuality quality;
	
	if (!this->createRandomLoot<UBasePersonalModule, TObjectPtr<UBaseModulesLootFunction>, EModuleQuality>(lootPoints, playerInventory, lootFunctions, personalModules, modulesGetter, personalClass, quality))
	{
		return;
	}

	if (quality == EModuleQuality::platinum)
	{
		personalClass = modules[personalClass];
	}

	playerInventory->addPersonalModule(NewObject<UBasePersonalModule>(playerInventory, personalClass));
}

void LootCreator::createRandomWeaponModule(int32 lootPoints, TObjectPtr<AInventory> playerInventory, const TArray<TObjectPtr<UBaseWeaponModulesLootFunction>>& lootFunctions) const
{

}
