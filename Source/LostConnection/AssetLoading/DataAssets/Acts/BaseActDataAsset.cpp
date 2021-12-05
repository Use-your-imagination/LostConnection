// Copyright (c) 2021 Use-your-imagination

#include "BaseActDataAsset.h"

FPrimaryAssetType UBaseActDataAsset::getPrimaryAssetType()
{
	return FPrimaryAssetType("Act");
}

FPrimaryAssetId UBaseActDataAsset::GetPrimaryAssetId() const
{
	PURE_VIRTUAL(UBaseActDataAsset::GetPrimaryAssetId, return FPrimaryAssetId(););
}
