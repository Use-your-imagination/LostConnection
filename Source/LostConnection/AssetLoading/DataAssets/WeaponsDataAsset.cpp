// Copyright (c) 2021 Use-your-imagination

#include "WeaponsDataAsset.h"

FPrimaryAssetId UWeaponsDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Weapons"), "Weapons");
}

FPrimaryAssetId UWeaponsDataAsset::GetPrimaryAssetId() const
{
	return UWeaponsDataAsset::getPrimaryAssetId();
}
