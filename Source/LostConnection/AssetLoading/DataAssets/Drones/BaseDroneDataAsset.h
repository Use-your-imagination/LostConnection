// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "BaseDroneDataAsset.generated.h"

UCLASS(Abstract, BlueprintType)
class LOSTCONNECTION_API UBaseDroneDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Drone, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ABaseDrone> drone;

	UPROPERTY(Category = VFX, EditDefaultsOnly)
	TArray<TObjectPtr<class UNiagaraSystem>> effects;

protected:
	static FPrimaryAssetType getPrimaryAssetType();

public:
	UBaseDroneDataAsset() = default;

	const TSubclassOf<class ABaseDrone>& getDrone() const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UBaseDroneDataAsset() = default;
};
