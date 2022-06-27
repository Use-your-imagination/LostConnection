// Copyright (c) 2021 Use Your Imagination

#include "StatusesDataAsset.h"

#include "Statuses/BaseStatus.h"

FPrimaryAssetId UStatusesDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Statuses"), "Statuses");
}

const TSubclassOf<UBaseStatus>& UStatusesDataAsset::operator [] (ETypeOfDamage damageType) const
{
	return ailments[damageType];
}

FPrimaryAssetId UStatusesDataAsset::GetPrimaryAssetId() const
{
	return UStatusesDataAsset::getPrimaryAssetId();
}
