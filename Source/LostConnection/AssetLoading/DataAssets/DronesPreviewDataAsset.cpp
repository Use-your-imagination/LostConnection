// Copyright (c) 2021 Use-your-imagination

#include "DronesPreviewDataAsset.h"

FDronePreview::FDronePreview() :
	mesh(USkeletalMesh::StaticClass()->GetDefaultObject<USkeletalMesh>())
{

}

FPrimaryAssetId UDronesPreviewDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("DronesPreview"), "DronesPreview");
}

TArray<const FDronePreview*> UDronesPreviewDataAsset::getDronesPreview() const
{
	return TArray<const FDronePreview*>
	{
		&SN4K3
	};
}

FPrimaryAssetId UDronesPreviewDataAsset::GetPrimaryAssetId() const
{
	return UDronesPreviewDataAsset::getPrimaryAssetId();
}
