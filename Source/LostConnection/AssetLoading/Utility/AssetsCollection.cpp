// Copyright (c) 2021 Use Your Imagination

#include "AssetsCollection.h"

template<typename DataAssetT>
TPair<TSubclassOf<UPrimaryDataAsset>, FPrimaryAssetId> AssetsCollection::getCreationData()
{
	return TPair<TSubclassOf<UPrimaryDataAsset>, FPrimaryAssetId>{ DataAssetT::StaticClass(), DataAssetT::getPrimaryAssetId() };
}

AssetsCollection::AssetsCollection()
{
	loadData.Add(AssetsCollection::getCreationData<UStatusesDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<UDronesPreviewDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<UWeaponsDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<UUIDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<UDefaultsDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<ULootDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<UAIDataAsset>());

	loadData.Add(AssetsCollection::getCreationData<USN4K3DataAsset>());

	loadData.Add(AssetsCollection::getCreationData<URuinedCityActDataAsset>());
}

AssetsCollection& AssetsCollection::get()
{
	static AssetsCollection instance;

	return instance;
}

const FPrimaryAssetId& AssetsCollection::operator [] (const TSubclassOf<UPrimaryDataAsset>& dataAsset) const
{
	return loadData[dataAsset];
}
