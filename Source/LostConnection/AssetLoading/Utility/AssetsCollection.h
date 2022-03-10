// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "AssetLoading/DataAssets/StatusesDataAsset.h"
#include "AssetLoading/DataAssets/DronesPreviewDataAsset.h"
#include "AssetLoading/DataAssets/WeaponsDataAsset.h"
#include "AssetLoading/DataAssets/UIDataAsset.h"
#include "AssetLoading/DataAssets/DefaultsDataAsset.h"
#include "AssetLoading/DataAssets/LootDataAsset.h"

#include "AssetLoading/DataAssets/Drones/SN4K3DataAsset.h"

#include "AssetLoading/DataAssets/Acts/RuinedCityActDataAsset.h"

class LOSTCONNECTION_API AssetsCollection
{
private:
	TMap<TSubclassOf<UPrimaryDataAsset>, FPrimaryAssetId> loadData;

private:
	template<typename DataAssetT>
	static TPair<TSubclassOf<UPrimaryDataAsset>, FPrimaryAssetId> getCreationData();

private:
	AssetsCollection();

	AssetsCollection(const AssetsCollection&) = delete;

	AssetsCollection(AssetsCollection&&) noexcept = delete;

	AssetsCollection& operator = (const AssetsCollection&) = delete;

	AssetsCollection& operator = (AssetsCollection&&) noexcept = delete;

	~AssetsCollection() = default;

public:
	static AssetsCollection& get();

	const FPrimaryAssetId& operator [] (const TSubclassOf<UPrimaryDataAsset>& dataAsset) const;
};

template<typename DataAssetT>
TPair<TSubclassOf<UPrimaryDataAsset>, FPrimaryAssetId> AssetsCollection::getCreationData()
{
	return TPair<TSubclassOf<UPrimaryDataAsset>, FPrimaryAssetId>{ DataAssetT::StaticClass(), DataAssetT::getPrimaryAssetId() };
}
