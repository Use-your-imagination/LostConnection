// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "StatusesDataAsset.generated.h"

UCLASS()
class LOSTCONNECTION_API UStatusesDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Ailments, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TMap<typeOfDamage, TSubclassOf<class UBaseStatus>> ailments;

	UPROPERTY(Category = Buffs, EditDefaultsOnly, Meta = (AllowPrivateAcess = "true"))
	UClass* SN4K3Reservator;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UStatusesDataAsset() = default;

	const TSubclassOf<class UBaseStatus>& operator [] (typeOfDamage damageType) const;

	const UClass* getDefaultSN4K3Reservator() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UStatusesDataAsset() = default;
};
