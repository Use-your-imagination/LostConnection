// Copyright (c) 2022 Use Your Imagination

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

	if (!manager.isAssetLoaded(ULootDataAsset::StaticClass()))
	{
		manager.syncLoadAsset(ULootDataAsset::StaticClass());
	}

	weaponsLootFunctions = createLootFunctions(manager.getLoot().getWeaponsLootFunctions());

	modulesLootFunctions = createLootFunctions(manager.getLoot().getModulesLootFunctions());

	weaponModulesLootFunctions = createLootFunctions(manager.getLoot().getWeaponModulesLootFunctions());
}

template<typename LootFunctionT>
TArray<TObjectPtr<LootFunctionT>> ALootManager::createLootFunctions(const TArray<TSubclassOf<LootFunctionT>>& lootFunctionClasses)
{
	TArray<TObjectPtr<LootFunctionT>> result;

	result.Reserve(lootFunctionClasses.Num());

	for (const auto& lootFunctionClass : lootFunctionClasses)
	{
		result.Add(NewObject<LootFunctionT>(this, lootFunctionClass));
	}

	return result;
}

void ALootManager::addRandomLoot(TObjectPtr<AInventory> playerInventory, int32 weaponsLootPoints, int32 modulesLootPoints, int32 weaponModulesLootPoints)
{
	const int32 maxSpendLootPoints = ULostConnectionAssetManager::get().getDefaults().getMaxSpendLootPoints();

	lootCreator.createRandomWeapon(weaponsLootPoints, playerInventory, weaponsLootFunctions);

	lootCreator.createRandomModule(modulesLootPoints, playerInventory, modulesLootFunctions);

	lootCreator.createRandomWeaponModule(weaponModulesLootPoints, playerInventory, weaponModulesLootFunctions);

	playerInventory->getPlayerState()->spendLootPoints(FMath::Min(FMath::Max3(weaponsLootPoints, modulesLootPoints, weaponModulesLootPoints), maxSpendLootPoints));
}

void ALootManager::spawnAmmo_Implementation(const TScriptInterface<IAmmoDropable>& ammoDropable)
{
	const ULootDataAsset& loot = ULostConnectionAssetManager::get().getLoot();
	TObjectPtr<UWorld> world = GetWorld();
	FTransform spawnTransform = ammoDropable->getCurrentPosition();

	if (Utility::checkChanceProc(IAmmoDropable::Execute_getSmallAmmoDropChance(ammoDropable.GetObject())))
	{
		world->SpawnActor<ABaseDroppedAmmo>(loot.getSmallAmmoClass(), spawnTransform);
	}

	if (Utility::checkChanceProc(IAmmoDropable::Execute_getLargeAmmoDropChance(ammoDropable.GetObject())))
	{
		world->SpawnActor<ABaseDroppedAmmo>(loot.getLargeAmmoClass(), spawnTransform);
	}

	if (Utility::checkChanceProc(IAmmoDropable::Execute_getEnergyAmmoDropChance(ammoDropable.GetObject())))
	{
		world->SpawnActor<ABaseDroppedAmmo>(loot.getEnergyAmmoClass(), spawnTransform);
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

void ALootManager::addRandomModule_Implementation(AInventory* playerInventory)
{
	int32 moduleLootPoints = playerInventory->getLootPoints();
	int32 otherLootPoints = moduleLootPoints * ULostConnectionAssetManager::get().getLoot().getSplitLootPointsCoefficient();

	this->addRandomLoot(playerInventory, otherLootPoints, moduleLootPoints, otherLootPoints);
}

void ALootManager::addRandomWeaponModule_Implementation(AInventory* playerInventory)
{
	int32 weaponModuleLootPoints = playerInventory->getLootPoints();
	int32 otherLootPoints = weaponModuleLootPoints * ULostConnectionAssetManager::get().getLoot().getSplitLootPointsCoefficient();

	this->addRandomLoot(playerInventory, otherLootPoints, otherLootPoints, weaponModuleLootPoints);
}

void ALootManager::spawnAmmoCall_Implementation(const TScriptInterface<IAmmoDropable>& ammoDropable)
{
	this->spawnAmmo(ammoDropable);
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
