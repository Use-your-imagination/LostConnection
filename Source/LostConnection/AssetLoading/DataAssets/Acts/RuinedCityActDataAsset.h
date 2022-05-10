// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "AssetLoading/DataAssets/Acts/BaseActDataAsset.h"

#include "RuinedCityActDataAsset.generated.h"

UCLASS()
class LOSTCONNECTION_API URuinedCityActDataAsset : public UBaseActDataAsset
{
	GENERATED_BODY()

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	URuinedCityActDataAsset() = default;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~URuinedCityActDataAsset() = default;
};
