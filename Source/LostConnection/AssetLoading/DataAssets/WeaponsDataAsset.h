// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "WeaponsDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UWeaponsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Weapons, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBaseWeapon>> weapons;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UWeaponsDataAsset() = default;

	TSubclassOf<class UBaseWeapon> operator [] (const TSubclassOf<class UBaseWeapon>& weapon) const;

	const TArray<TSubclassOf<class UBaseWeapon>>& getWeapons() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UWeaponsDataAsset() = default;
};
