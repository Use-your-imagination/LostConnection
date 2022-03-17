// Copyright (c) 2021 Use-your-imagination

#include "DefaultsDataAsset.h"

#include "WorldPlaceables/DeathPlaceholder.h"
#include "Weapons/BaseWeapon.h"
#include "Constants/Constants.h"

FPrimaryAssetId UDefaultsDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Default"), "DefaultAssets");
}

UDefaultsDataAsset::UDefaultsDataAsset() :
	maxSmallAmmoCount(UConstants::defaultSmallAmmoMaxCount),
	maxLargeAmmoCount(UConstants::defaultLargeAmmoMaxCount),
	maxEnergyAmmoCount(UConstants::defaultEnergyAmmoMaxCount)
{

}

const TSubclassOf<ADeathPlaceholder>& UDefaultsDataAsset::getDeathPlaceholder() const
{
	return deathPlaceholder;
}

const FColor& UDefaultsDataAsset::operator [] (EWeaponRarity rarity) const
{
	switch (rarity)
	{
	case EWeaponRarity::normal:
		return normalRarityWeaponColor;

	case EWeaponRarity::rare:
		return rareRarityWeaponColor;

	case EWeaponRarity::epic:
		return epicRarityWeaponColor;

	case EWeaponRarity::legendary:
		return legendaryRarityWeaponColor;
	}

	return FColor::Emerald;
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

FPrimaryAssetId UDefaultsDataAsset::GetPrimaryAssetId() const
{
	return UDefaultsDataAsset::getPrimaryAssetId();
}
