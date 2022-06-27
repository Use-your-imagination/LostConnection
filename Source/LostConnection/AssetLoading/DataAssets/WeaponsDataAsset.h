// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "WeaponsDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UWeaponsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Weapons, EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<TSubclassOf<class UBaseWeapon>> weapons;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UWeaponsDataAsset() = default;

	TSubclassOf<class UBaseWeapon> operator [] (const TSubclassOf<class UBaseWeapon>& weapon) const;

	const TArray<TSubclassOf<class UBaseWeapon>>& getWeapons() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UWeaponsDataAsset() = default;
};
