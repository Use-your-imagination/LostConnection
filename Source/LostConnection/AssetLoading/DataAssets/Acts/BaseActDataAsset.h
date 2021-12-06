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
	UPROPERTY(Category = StartingLocations, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> startingLocations;

	UPROPERTY(Category = Rooms, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> rooms;

	UPROPERTY(Category = SecretRooms, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> secretRooms;

	UPROPERTY(Category = Warehouses, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> warehouses;

	UPROPERTY(Category = BossRooms, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> bossRoom;

protected:
	static FPrimaryAssetType getPrimaryAssetType();

public:
	UBaseActDataAsset() = default;

	virtual const TArray<TSoftObjectPtr<UWorld>>& getRooms() const final;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UBaseActDataAsset() = default;
};
