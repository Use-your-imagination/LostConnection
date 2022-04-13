// Copyright (c) 2022 Use-your-imagination

#include "LootManager.h"

#include "Engine/LostConnectionPlayerState.h"
#include "Engine/LostConnectionPlayerController.h"
#include "Constants/Constants.h"
#include "Utility/Utility.h"
#include "WorldPlaceables/BaseDroppedAmmo.h"
#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"

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

void ALootManager::spawnAmmo_Implementation(UObject* ammoDropable)
{
	const ULootDataAsset& loot = ULostConnectionAssetManager::get().getLoot();
	TObjectPtr<ALostConnectionGameState> gameState = Utility::getGameState(this);
	FTransform spawnTransform = UUtilityBlueprintFunctionLibrary::getAmmoDropableCurrentPosition(ammoDropable);

	if (Utility::checkChanceProc(IAmmoDropable::Execute_getSmallAmmoDropChance(ammoDropable)))
	{
		gameState->spawn<ABaseDroppedAmmo>(loot.getSmallAmmoClass(), spawnTransform)->FinishSpawning({}, true);
	}

	if (Utility::checkChanceProc(IAmmoDropable::Execute_getLargeAmmoDropChance(ammoDropable)))
	{
		gameState->spawn<ABaseDroppedAmmo>(loot.getLargeAmmoClass(), spawnTransform)->FinishSpawning({}, true);
	}

	if (Utility::checkChanceProc(IAmmoDropable::Execute_getEnergyAmmoDropChance(ammoDropable)))
	{
		gameState->spawn<ABaseDroppedAmmo>(loot.getEnergyAmmoClass(), spawnTransform)->FinishSpawning({}, true);
	}
}

ALootManager::ALootManager()
{
	bReplicates = true;

	bOnlyRelevantToOwner = true;
}

void ALootManager::init_Implementation(APlayerController* playerController)
{
	this->SetOwner(playerController);
}

void ALootManager::addRandomWeapon_Implementation(AInventory* playerInventory)
{
	int32 weaponLootPoints = playerInventory->getLootPoints();
	int32 otherLootPoints = weaponLootPoints * ULostConnectionAssetManager::get().getLoot().getSplitLootPointsCoefficient();

	this->addRandomLoot(playerInventory, weaponLootPoints, otherLootPoints, otherLootPoints);
}

void ALootManager::spawnAmmoCall(TScriptInterface<IAmmoDropable> ammoDropable)
{
	this->spawnAmmo(ammoDropable.GetObject());
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
