// Copyright (c) 2021 Use-your-imagination

#include "DronesPreviewDataAsset.h"

FPrimaryAssetId UDronesPreviewDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("DronesPreview"), "DronesPreview");
}

FPrimaryAssetId UDronesPreviewDataAsset::GetPrimaryAssetId() const
{
	return UDronesPreviewDataAsset::getPrimaryAssetId();
}
