// Copyright (c) 2022 Use-your-imagination

#include "LootManager.h"

#include "Engine/LostConnectionPlayerState.h"
#include "Constants/Constants.h"

void ALootManager::BeginPlay()
{
	Super::BeginPlay();

	ULostConnectionAssetManager& manager = ULostConnectionAssetManager::get();

	weaponsLootFunctions = createLootFunctions(manager.getLoot().getWeaponsLootFunctions());

	modulesLootFunctions = createLootFunctions(manager.getLoot().getModulesLootFunctions());

	weaponModulesLootFunctions = createLootFunctions(manager.getLoot().getWeaponModulesLootFunctions());
}

template<typename LootFunctionT>
TArray<LootFunctionT*> ALootManager::createLootFunctions(const TArray<TSubclassOf<LootFunctionT>>& lootFunctionClasses)
{
	TArray<LootFunctionT*> result;

	result.Reserve(lootFunctionClasses.Num());

	for (const auto& lootFunctionClass : lootFunctionClasses)
	{
		result.Add(NewObject<LootFunctionT>(this, lootFunctionClass));
	}

	return result;
}

void ALootManager::addRandomWeapon_Implementation(UInventory* playerInventory)
{
	playerInventory->getPlayerState()->spendLootPoints(FMath::Min(playerInventory->getLootPoints(), UConstants::maxSpendLootPoints));

	lootCreator.createRandomWeapon(playerInventory);
}

const TArray<UBaseWeaponsLootFunction*>& ALootManager::getWeaponsLootFunctions() const
{
	return weaponsLootFunctions;
}

const TArray<UBaseModulesLootFunction*>& ALootManager::getModulesLootFunctions() const
{
	return modulesLootFunctions;
}

const TArray<UBaseWeaponModulesLootFunction*>& ALootManager::getWeaponModulesLootFunctions() const
{
	return weaponModulesLootFunctions;
}

FText ALootManager::getWeaponsDropChance(int32 lootPoints) const
{
	FString result;

	for (UBaseWeaponsLootFunction* weaponLootFunction : weaponsLootFunctions)
	{
		if (result.Len())
		{
			result += '\n';
		}

		result += FString::Printf(TEXT("%s: %.2f", *weaponLootFunction->getLootName().ToString(), weaponLootFunction->calculateLootChance(lootPoints)));
	}

	return FText::FromString(result);
}
