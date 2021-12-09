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

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UStatusesDataAsset() = default;

	const UClass* operator [] (typeOfDamage damageType) const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UStatusesDataAsset() = default;
};
