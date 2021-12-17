// Copyright (c) 2021 Use-your-imagination

#include "SN4K3DataAsset.h"

FPrimaryAssetId USN4K3DataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(USN4K3DataAsset::getPrimaryAssetType(), "SN4K3");
}

FPrimaryAssetId USN4K3DataAsset::GetPrimaryAssetId() const
{
	return USN4K3DataAsset::getPrimaryAssetId();
}
