// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "AssetLoading/DataAssets/Drones/BaseDroneDataAsset.h"

#include "SN4K3DataAsset.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3DataAsset : public UBaseDroneDataAsset
{
	GENERATED_BODY()

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	USN4K3DataAsset() = default;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~USN4K3DataAsset() = default;
};
