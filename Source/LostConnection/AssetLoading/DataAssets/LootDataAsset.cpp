// Copyright (c) 2022 Use-your-imagination

#include "LootDataAsset.h"

#include "Kismet/KismetMathLibrary.h"

#include "Weapons/BaseWeapon.h"
#include "Modules/BasePersonalModule.h"
#include "Modules/BaseWeaponModule.h"

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

TSubclassOf<UBasePersonalModule> ULootDataAsset::operator[](const TSubclassOf<UBasePersonalModule>& personalModule) const
{
	return findSubclass(personalModules, personalModule);
}

TSubclassOf<UBaseWeaponModule> ULootDataAsset::operator[](const TSubclassOf<UBaseWeaponModule>& weaponModule) const
{
	return findSubclass(weaponModules, weaponModule);
}

const TArray<TSubclassOf<UBaseWeapon>>& ULootDataAsset::getWeapons() const
{
	return weapons;
}

const TArray<TSubclassOf<UBasePersonalModule>>& ULootDataAsset::getPersonalModules() const
{
	return personalModules;
}

const TArray<TSubclassOf<UBaseWeaponModule>>& ULootDataAsset::getWeaponModules() const
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
