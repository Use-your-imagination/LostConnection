// Copyright (c) 2021 Use-your-imagination

#include "BaseActDataAsset.h"

FPrimaryAssetType UBaseActDataAsset::getPrimaryAssetType()
{
	return FPrimaryAssetType("Act");
}

const TArray<TSoftObjectPtr<UWorld>>& UBaseActDataAsset::getRooms() const
{
	return rooms;
}

FPrimaryAssetId UBaseActDataAsset::GetPrimaryAssetId() const
{
	PURE_VIRTUAL(UBaseActDataAsset::GetPrimaryAssetId, return FPrimaryAssetId(););
}
