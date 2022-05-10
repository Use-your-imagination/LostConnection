// Copyright (c) 2021 Use Your Imagination

#include "WeaponsDataAsset.h"

#include "Kismet/KismetMathLibrary.h"

#include "Weapons/BaseWeapon.h"

FPrimaryAssetId UWeaponsDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Weapons"), "Weapons");
}

TSubclassOf<UBaseWeapon> UWeaponsDataAsset::operator [] (const TSubclassOf<UBaseWeapon>& weapon) const
{
	for (const auto& i : weapons)
	{
		if (UKismetMathLibrary::ClassIsChildOf(i, weapon))
		{
			return i;
		}
	}

	return nullptr;
}

const TArray<TSubclassOf<UBaseWeapon>>& UWeaponsDataAsset::getWeapons() const
{
	return weapons;
}

FPrimaryAssetId UWeaponsDataAsset::GetPrimaryAssetId() const
{
	return UWeaponsDataAsset::getPrimaryAssetId();
}
