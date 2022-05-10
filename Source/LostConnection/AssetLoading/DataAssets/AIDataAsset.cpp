// Copyright (c) 2022 Use Your Imagination

#include "AIDataAsset.h"

FPrimaryAssetId UAIDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("AI"), "AI");
}

const FName& UAIDataAsset::getTargetKey() const
{
	return targetKey;
}

FPrimaryAssetId UAIDataAsset::GetPrimaryAssetId() const
{
	return UAIDataAsset::getPrimaryAssetId();
}
