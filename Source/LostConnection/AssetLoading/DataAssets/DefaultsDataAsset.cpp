// Copyright (c) 2021 Use-your-imagination

#include "DefaultsDataAsset.h"

#include "WorldPlaceables/DeathPlaceholder.h"
#include "Weapons/BaseWeapon.h"

FPrimaryAssetId UDefaultsDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Default"), "DefaultAssets");
}

const TSubclassOf<ADeathPlaceholder>& UDefaultsDataAsset::getDeathPlaceholder() const
{
	return deathPlaceholder;
}

const FColor& UDefaultsDataAsset::operator [] (weaponRarity rarity) const
{
	switch (rarity)
	{
	case weaponRarity::normal:
		return normalRarityWeaponColor;

	case weaponRarity::rare:
		return rareRarityWeaponColor;

	case weaponRarity::epic:
		return epicRarityWeaponColor;

	case weaponRarity::legendary:
		return legendaryRarityWeaponColor;
	}

	return FColor::Emerald;
}

FPrimaryAssetId UDefaultsDataAsset::GetPrimaryAssetId() const
{
	return UDefaultsDataAsset::getPrimaryAssetId();
}
