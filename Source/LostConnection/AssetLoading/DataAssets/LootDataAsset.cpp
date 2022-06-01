// Copyright (c) 2022 Use Your Imagination

#include "LootDataAsset.h"

#include "Kismet/KismetMathLibrary.h"

#include "Weapons/BaseWeapon.h"
#include "Modules/BasePersonalModule.h"
#include "Modules/BaseWeaponModule.h"
#include "WorldPlaceables/BaseDroppedAmmo.h"

template<typename T>
static TSubclassOf<T> findSubclass(const TArray<TSubclassOf<T>>& classes, const TSubclassOf<T>& subclass);

FPrimaryAssetId ULootDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Loot"), "Loot");
}

TSubclassOf<UBaseWeapon> ULootDataAsset::operator [] (const TSubclassOf<UBaseWeapon>& weapon) const
{
	return findSubclass(weapons, weapon);
}

const TArray<TSubclassOf<UBaseWeapon>>& ULootDataAsset::getWeapons() const
{
	return weapons;
}

const TMap<TSubclassOf<UBasePersonalModule>, FPersonalModulesCreator>& ULootDataAsset::getPersonalModules() const
{
	return personalModules;
}

const TMap<TSubclassOf<UBaseWeaponModule>, FWeaponModulesCreator>& ULootDataAsset::getWeaponModules() const
{
	return weaponModules;
}

const TArray<TSubclassOf<UBaseWeaponsLootFunction>>& ULootDataAsset::getWeaponsLootFunctions() const
{
	return weaponsLootFunctions;
}

const TArray<TSubclassOf<UBaseModulesLootFunction>>& ULootDataAsset::getModulesLootFunctions() const
{
	return modulesLootFunctions;
}

const TArray<TSubclassOf<UBaseWeaponModulesLootFunction>>& ULootDataAsset::getWeaponModulesLootFunctions() const
{
	return weaponModulesLootFunctions;
}

float ULootDataAsset::getSplitLootPointsCoefficient() const
{
	return splitLootPointsCoefficient;
}

const TSubclassOf<ABaseDroppedAmmo>& ULootDataAsset::getSmallAmmoClass() const
{
	return smallAmmoClass;
}

const TSubclassOf<ABaseDroppedAmmo>& ULootDataAsset::getLargeAmmoClass() const
{
	return largeAmmoClass;
}

const TSubclassOf<ABaseDroppedAmmo>& ULootDataAsset::getEnergyAmmoClass() const
{
	return energyAmmoClass;
}

FPrimaryAssetId ULootDataAsset::GetPrimaryAssetId() const
{
	return ULootDataAsset::getPrimaryAssetId();
}

template<typename T>
TSubclassOf<T> findSubclass(const TArray<TSubclassOf<T>>& classes, const TSubclassOf<T>& subclass)
{
	for (const auto& i : classes)
	{
		if (UKismetMathLibrary::ClassIsChildOf(i, subclass))
		{
			return i;
		}
	}

	return nullptr;
}
