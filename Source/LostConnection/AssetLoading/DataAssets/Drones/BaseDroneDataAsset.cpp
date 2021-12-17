// Copyright (c) 2021 Use-your-imagination

#include "BaseDroneDataAsset.h"

#include "Characters/BaseDrone.h"

FPrimaryAssetType UBaseDroneDataAsset::getPrimaryAssetType()
{
	return FPrimaryAssetType("Drones");
}

const TSubclassOf<ABaseDrone>& UBaseDroneDataAsset::getDrone() const
{
	return drone;
}

FPrimaryAssetId UBaseDroneDataAsset::GetPrimaryAssetId() const
{
	PURE_VIRTUAL(UBaseDroneDataAsset::GetPrimaryAssetId, return FPrimaryAssetId(););
}
