// Copyright (c) 2021 Use Your Imagination

#include "BaseActDataAsset.h"

#include "Characters/AI/BaseBot.h"

FPrimaryAssetType UBaseActDataAsset::getPrimaryAssetType()
{
	return FPrimaryAssetType("Act");
}

const TArray<TSoftObjectPtr<UWorld>>& UBaseActDataAsset::getRooms() const
{
	return rooms;
}

const TArray<TSubclassOf<ABaseBot>>& UBaseActDataAsset::operator [] (EBotType type) const
{
	static TArray<TSubclassOf<ABaseBot>> empty;

	switch (type)
	{
	case EBotType::melee:
		return meleeBots;

	case EBotType::ranged:
		return rangedBots;

	case EBotType::sniper:
		return sniperBots;

	case EBotType::caster:
		return casterBots;

	case EBotType::support:
		return supportBots;

	case EBotType::assassin:
		return assassinBots;

	default:
		return empty;
	}
}

FPrimaryAssetId UBaseActDataAsset::GetPrimaryAssetId() const
{
	PURE_VIRTUAL(UBaseActDataAsset::GetPrimaryAssetId, return FPrimaryAssetId(););
}
