// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "BaseActDataAsset.generated.h"

UCLASS(Blueprintable)
class LOSTCONNECTION_API UBaseActDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Rooms, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> rooms;

protected:
	static FPrimaryAssetType getPrimaryAssetType();

public:
	UBaseActDataAsset() = default;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UBaseActDataAsset() = default;
};
