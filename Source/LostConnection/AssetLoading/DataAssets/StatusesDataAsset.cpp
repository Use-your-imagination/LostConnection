// Copyright (c) 2021 Use-your-imagination

#include "StatusesDataAsset.h"

#include "Statuses/BaseStatus.h"

FPrimaryAssetId UStatusesDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("Statuses"), "Statuses");
}

const UClass* UStatusesDataAsset::operator [] (typeOfDamage damageType) const
{
	return ailments[damageType].Get();
}

FPrimaryAssetId UStatusesDataAsset::GetPrimaryAssetId() const
{
	return UStatusesDataAsset::getPrimaryAssetId();
}
