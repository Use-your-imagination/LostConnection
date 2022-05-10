// Copyright (c) 2021 Use Your Imagination

#include "BaseActDataAsset.h"

#include "Characters/BaseBot.h"

FPrimaryAssetType UBaseActDataAsset::getPrimaryAssetType()
{
	return FPrimaryAssetType("Act");
}

const TArray<TSoftObjectPtr<UWorld>>& UBaseActDataAsset::getRooms() const
{
	return rooms;
}

const TArray<TSubclassOf<ABaseBot>>& UBaseActDataAsset::getBots() const
{
	return bots;
}

FPrimaryAssetId UBaseActDataAsset::GetPrimaryAssetId() const
{
	PURE_VIRTUAL(UBaseActDataAsset::GetPrimaryAssetId, return FPrimaryAssetId(););
}
