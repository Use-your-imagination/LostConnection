// Copyright (c) 2021 Use-your-imagination

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
	UPROPERTY(Category = Ailments, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TMap<ETypeOfDamage, TSubclassOf<class UBaseStatus>> ailments;

	UPROPERTY(Category = "Buffs|SN4K3", EditDefaultsOnly, Meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class USN4K3Reservator> SN4K3Reservator;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UStatusesDataAsset() = default;

	const TSubclassOf<class UBaseStatus>& operator [] (ETypeOfDamage damageType) const;

	const TSubclassOf<class USN4K3Reservator>& getDefaultSN4K3Reservator() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UStatusesDataAsset() = default;
};
