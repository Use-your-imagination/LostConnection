// Copyright (c) 2021 Use Your Imagination

#include "DronesPreviewDataAsset.h"

FDronePreview::FDronePreview() :
	mesh(USkeletalMesh::StaticClass()->GetDefaultObject<USkeletalMesh>()),
	droneInformation(UStringTable::StaticClass()->GetDefaultObject<UStringTable>())
{

}

FPrimaryAssetId UDronesPreviewDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("DronesPreview"), "DronesPreview");
}

TArray<const FDronePreview*> UDronesPreviewDataAsset::getDronesPreview() const
{
	return
	{
		&SN4K3PreviewData
	};
}

FPrimaryAssetId UDronesPreviewDataAsset::GetPrimaryAssetId() const
{
	return UDronesPreviewDataAsset::getPrimaryAssetId();
}
