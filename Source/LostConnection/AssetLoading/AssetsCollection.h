// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "DataAssets/StatusesDataAsset.h"

class LOSTCONNECTION_API AssetsCollection
{
private:
	TMap<UClass*, FPrimaryAssetId> loadData;

private:
	template<typename DataAssetT>
	static TPair<UClass*, FPrimaryAssetId> getCreationData();

private:
	AssetsCollection();

	AssetsCollection(const AssetsCollection&) = delete;

	AssetsCollection(AssetsCollection&&) noexcept = delete;

	AssetsCollection& operator = (const AssetsCollection&) = delete;

	AssetsCollection& operator = (AssetsCollection&&) noexcept = delete;

	~AssetsCollection() = default;

public:
	static AssetsCollection& get();

	const FPrimaryAssetId& operator [] (UClass* dataAsset) const;
};

template<typename DataAssetT>
TPair<UClass*, FPrimaryAssetId> AssetsCollection::getCreationData()
{
	return TPair<UClass*, FPrimaryAssetId>{ DataAssetT::StaticClass(), DataAssetT::getPrimaryAssetId() };
}
