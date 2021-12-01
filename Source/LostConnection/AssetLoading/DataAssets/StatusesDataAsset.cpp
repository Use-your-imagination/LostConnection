// Copyright (c) 2021 Use-your-imagination

#include "StatusesDataAsset.h"

#include "Statuses/BaseStatus.h"

FPrimaryAssetId UStatusesDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Statuses"), "Statuses");
}

const TArray<TSoftClassPtr<UBaseStatus>>& UStatusesDataAsset::getAilments() const
{
	return ailments;
}

FPrimaryAssetId UStatusesDataAsset::GetPrimaryAssetId() const
{
	return UStatusesDataAsset::getPrimaryAssetId();
}
