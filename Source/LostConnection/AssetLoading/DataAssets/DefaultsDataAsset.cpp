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

FPrimaryAssetId UDefaultsDataAsset::GetPrimaryAssetId() const
{
	return UDefaultsDataAsset::getPrimaryAssetId();
}
