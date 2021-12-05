// Copyright (c) 2021 Use-your-imagination

#include "RuinedCityActDataAsset.h"

FPrimaryAssetId URuinedCityActDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(URuinedCityActDataAsset::getPrimaryAssetType(), "RuinedCity");
}

FPrimaryAssetId URuinedCityActDataAsset::GetPrimaryAssetId() const
{
	return URuinedCityActDataAsset::getPrimaryAssetId();
}
