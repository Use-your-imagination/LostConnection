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

void ALootManager::addRandomLoot(UInventory* playerInventory, int32 weaponsLootPoints, int32 modulesLootPoints, int32 weaponModulesLootPoints)
{
	lootCreator.createRandomWeapon(weaponsLootPoints, playerInventory, weaponsLootFunctions);

	playerInventory->getPlayerState()->spendLootPoints(FMath::Min(FMath::Max3(weaponsLootPoints, modulesLootPoints, weaponModulesLootPoints), UConstants::maxSpendLootPoints));
}

void ALootManager::addRandomWeapon_Implementation(UInventory* playerInventory)
{
	int32 weaponLootPoints = playerInventory->getLootPoints();
	int32 otherLootPoints = weaponLootPoints * ULostConnectionAssetManager::get().getLoot().getSplitLootPointsCoefficient();

	this->addRandomLoot(playerInventory, weaponLootPoints, otherLootPoints, otherLootPoints);
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

		float chance = weaponLootFunction->calculateLootChance(lootPoints);
		const FString& weaponName = weaponLootFunction->getLootName().ToString();

		if (chance < 1.0f)
		{
			result += FString::Printf(TEXT("%s: < 1%%"), *weaponName);
		}
		else
		{
			result += FString::Printf(TEXT("%s: %.0f%%"), *weaponName, chance);
		}
	}

	return FText::FromString(result);
}
