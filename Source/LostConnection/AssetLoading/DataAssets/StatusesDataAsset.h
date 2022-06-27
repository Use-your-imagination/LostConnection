// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "StatusesDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UStatusesDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Ailments, EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TMap<ETypeOfDamage, TSubclassOf<class UBaseStatus>> ailments;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UStatusesDataAsset() = default;

	const TSubclassOf<class UBaseStatus>& operator [] (ETypeOfDamage damageType) const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UStatusesDataAsset() = default;
};
