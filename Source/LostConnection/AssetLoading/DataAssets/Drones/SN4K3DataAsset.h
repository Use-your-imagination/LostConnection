// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "AssetLoading/DataAssets/Drones/BaseDroneDataAsset.h"

#include "SN4K3DataAsset.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3DataAsset : public UBaseDroneDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> headUI;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	USN4K3DataAsset() = default;

	const TSubclassOf<UUserWidget>& getHeadUI() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~USN4K3DataAsset() = default;
};
