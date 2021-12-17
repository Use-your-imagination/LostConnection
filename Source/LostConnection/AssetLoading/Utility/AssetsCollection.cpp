// Copyright (c) 2021 Use-your-imagination

#include "AssetsCollection.h"

AssetsCollection::AssetsCollection()
{
	loadData.Add(AssetsCollection::getCreationData<UStatusesDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<UDronesPreviewDataAsset>());
	loadData.Add(AssetsCollection::getCreationData<UWeaponsDataAsset>());

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
