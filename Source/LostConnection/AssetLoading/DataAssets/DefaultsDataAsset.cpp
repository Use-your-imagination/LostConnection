// Copyright (c) 2021 Use Your Imagination

#include "DefaultsDataAsset.h"

#include "WorldPlaceables/DeathPlaceholder.h"
#include "Weapons/BaseWeapon.h"
#include "Constants/Constants.h"

FShootThroughSurface::FShootThroughSurface() :
	flatDamageReducation(100.0f),
	percentDamageReduction(50.0f)
{

}

FPrimaryAssetId UDefaultsDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Default"), "DefaultAssets");
}

UDefaultsDataAsset::UDefaultsDataAsset() :
	maxSmallAmmoCount(700),
	maxLargeAmmoCount(240),
	maxEnergyAmmoCount(50),
	maxSpendLootPoints(20'000),
	maxShootDistance(20'000.0f),
	personalModulesLimit(8)
{

}

const TSubclassOf<ADeathPlaceholder>& UDefaultsDataAsset::getDeathPlaceholder() const
{
	return deathPlaceholder;
}

const FLinearColor& UDefaultsDataAsset::operator [] (EWeaponRarity rarity) const
{
	return weaponsRarityColor[rarity];
}

const FLinearColor& UDefaultsDataAsset::operator [] (EModuleQuality quality) const
{
	return modulesQualityColor[quality];
}

const FShootThroughSurface& UDefaultsDataAsset::operator [] (const TWeakObjectPtr<UPhysicalMaterial>& physicalMaterial) const
{
	check(physicalMaterial.IsValid());

	return shootThroughSurfaces[UPhysicalMaterial::DetermineSurfaceType(physicalMaterial.Get())];
}

int32 UDefaultsDataAsset::getMaxSmallAmmoCount() const
{
	return maxSmallAmmoCount;
}

int32 UDefaultsDataAsset::getMaxLargeAmmoCount() const
{
	return maxLargeAmmoCount;
}

int32 UDefaultsDataAsset::getMaxEnergyAmmoCount() const
{
	return maxEnergyAmmoCount;
}

float UDefaultsDataAsset::getResistHardcap() const
{
	return resistHardcap;
}

int32 UDefaultsDataAsset::getModulesToNextTier() const
{
	return modulesToNextTier;
}

int32 UDefaultsDataAsset::getMaxSpendLootPoints() const
{
	return maxSpendLootPoints;
}

int32 UDefaultsDataAsset::getMaxShootDistance() const
{
	return maxShootDistance;
}

int32 UDefaultsDataAsset::getPersonalModulesLimit() const
{
	return personalModulesLimit;
}

FPrimaryAssetId UDefaultsDataAsset::GetPrimaryAssetId() const
{
	return UDefaultsDataAsset::getPrimaryAssetId();
}
