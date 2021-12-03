// Copyright (c) 2021 Use-your-imagination

#include "WeaponsDataAsset.h"

#include "Weapons/BaseWeapon.h"

FPrimaryAssetId UWeaponsDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Weapons"), "Weapons");
}

TSubclassOf<UBaseWeapon> UWeaponsDataAsset::operator [] (const TSubclassOf<UBaseWeapon>& weapon) const
{
	TSubclassOf<UBaseWeapon> result = nullptr;

	for (const auto& i : weapons)
	{
		if (i->IsChildOf(weapon.Get()))
		{
			result = i.Get();

			break;
		}
	}

	return result;
}

FPrimaryAssetId UWeaponsDataAsset::GetPrimaryAssetId() const
{
	return UWeaponsDataAsset::getPrimaryAssetId();
}
