// Copyright (c) 2021 Use-your-imagination

#include "StatusesDataAsset.h"

#include "Statuses/BaseStatus.h"

FPrimaryAssetId UStatusesDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Statuses"), "Statuses");
}

const TSubclassOf<UBaseStatus>& UStatusesDataAsset::operator [] (typeOfDamage damageType) const
{
	return ailments[damageType];
}

const TSubclassOf<USN4K3Reservator>& UStatusesDataAsset::getDefaultSN4K3Reservator() const
{
	return SN4K3Reservator;
}

FPrimaryAssetId UStatusesDataAsset::GetPrimaryAssetId() const
{
	return UStatusesDataAsset::getPrimaryAssetId();
}
