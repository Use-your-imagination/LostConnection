// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "BaseActDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UBaseActDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Levels, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> startingLocations;

	UPROPERTY(Category = Levels, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> rooms;

	UPROPERTY(Category = Levels, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> secretRooms;

	UPROPERTY(Category = Levels, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> warehouses;

	UPROPERTY(Category = Levels, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> bossRooms;

	UPROPERTY(Category = AI, EditDefaultsOnly)
	TArray<TSubclassOf<class ABaseBot>> bots;

protected:
	static FPrimaryAssetType getPrimaryAssetType();

public:
	UBaseActDataAsset() = default;

	virtual const TArray<TSoftObjectPtr<UWorld>>& getRooms() const final;

	virtual const TArray<TSubclassOf<class ABaseBot>>& getBots() const final;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UBaseActDataAsset() = default;
};
