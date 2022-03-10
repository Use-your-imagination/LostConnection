// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "LootDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ULootDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Weapons, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBaseWeapon>> weapons;

	UPROPERTY(Category = "Modules|Personal", EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBasePersonalModule>> personalModules;

	UPROPERTY(Category = "Modules|Weapon", EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBaseWeaponModule>> weaponModules;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	ULootDataAsset() = default;

	TSubclassOf<class UBaseWeapon> operator [] (const TSubclassOf<class UBaseWeapon>& weapon) const;

	TSubclassOf<class UBasePersonalModule> operator [] (const TSubclassOf<class UBasePersonalModule>& personalModule) const;

	TSubclassOf<class UBaseWeaponModule> operator [] (const TSubclassOf<class UBaseWeaponModule>& weaponModule) const;

	const TArray<TSubclassOf<class UBaseWeapon>>& getWeapons() const;

	const TArray<TSubclassOf<class UBasePersonalModule>>& getPersonalModules() const;

	const TArray<TSubclassOf<class UBaseWeaponModule>>& getWeaponModules() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~ULootDataAsset() = default;
};
