// Copyright (c) 2021 Use-your-imagination

#include "AssetsCollection.h"

AssetsCollection::AssetsCollection()
{
	loadData.Add(AssetsCollection::getCreationData<UStatusesDataAsset>());
}

AssetsCollection& AssetsCollection::get()
{
	static AssetsCollection instance;

	return instance;
}

const FPrimaryAssetId& AssetsCollection::operator [] (UClass* dataAsset) const
{
	return loadData[dataAsset];
}
