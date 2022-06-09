// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Inventory/Inventory.h"
#include "Maths/Loot/BaseWeaponsLootFunction.h"
#include "Maths/Loot/BaseModulesLootFunction.h"
#include "Maths/Loot/BaseWeaponModulesLootFunction.h"

class LOSTCONNECTION_API LootCreator
{
private:
	const TFunction<EWeaponRarity(TObjectPtr<UBaseWeaponsLootFunction>)> weaponsGetter;
	const TFunction<EModuleQuality(TObjectPtr<UBaseModulesLootFunction>)> modulesGetter;
	const TFunction<EModuleQuality(TObjectPtr<UBaseWeaponModulesLootFunction>)> weaponModulesGetter;

private:
	template<typename T, typename LootFunctionT, typename RangeEnumT>
	bool createRandomLoot
	(
		int32 lootPoints,
		TObjectPtr<AInventory> playerInventory,
		const TArray<LootFunctionT>& lootFunctions,
		const TArray<TSubclassOf<T>>& classes,
		const TFunction<RangeEnumT(LootFunctionT)>& getRangeEnum,
		TSubclassOf<T>& classToCreate,
		RangeEnumT& resultRange
	) const;

	template<typename T>
	TObjectPtr<T> createModule(const TSubclassOf<T>& subclass, TObjectPtr<AInventory> playerInventory, EModuleQuality quality) const;

public:
	LootCreator();

	void createRandomWeapon(int32 lootPoints, TObjectPtr<AInventory> playerInventory, const TArray<TObjectPtr<UBaseWeaponsLootFunction>>& lootFunctions) const;

	void createRandomModule(int32 lootPoints, TObjectPtr<AInventory> playerInventory, const TArray<TObjectPtr<UBaseModulesLootFunction>>& lootFunctions) const;

	void createRandomWeaponModule(int32 lootPoints, TObjectPtr<AInventory> playerInventory, const TArray<TObjectPtr<UBaseWeaponModulesLootFunction>>& lootFunctions) const;

	~LootCreator() = default;
};
