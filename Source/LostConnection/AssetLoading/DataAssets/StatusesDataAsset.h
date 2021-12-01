// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "StatusesDataAsset.generated.h"

UCLASS()
class LOSTCONNECTION_API UStatusesDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Ailments, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSoftClassPtr<class UBaseStatus>> ailments;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UStatusesDataAsset() = default;

	const TArray<TSoftClassPtr<class UBaseStatus>>& getAilments() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UStatusesDataAsset() = default;
};
