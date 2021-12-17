// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "BaseDroneDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UBaseDroneDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Drone, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ABaseDrone> drone;

protected:
	static FPrimaryAssetType getPrimaryAssetType();

public:
	UBaseDroneDataAsset() = default;

	const TSubclassOf<class ABaseDrone>& getDrone() const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UBaseDroneDataAsset() = default;
};
