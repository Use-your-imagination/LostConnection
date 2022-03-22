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

void ALootManager::addRandomLoot(AInventory* playerInventory, int32 weaponsLootPoints, int32 modulesLootPoints, int32 weaponModulesLootPoints)
{
	lootCreator.createRandomWeapon(weaponsLootPoints, playerInventory, weaponsLootFunctions);

	playerInventory->getPlayerState()->spendLootPoints(FMath::Min(FMath::Max3(weaponsLootPoints, modulesLootPoints, weaponModulesLootPoints), UConstants::maxSpendLootPoints));
}

ALootManager::ALootManager()
{
	bReplicates = true;

	bAlwaysRelevant = true;
}

void ALootManager::addRandomWeapon_Implementation(AInventory* playerInventory)
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
