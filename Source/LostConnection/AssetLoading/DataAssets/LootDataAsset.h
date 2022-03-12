// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "Maths/Loot/BaseWeaponsLootFunction.h"
#include "Maths/Loot/BaseModulesLootFunction.h"
#include "Maths/Loot/BaseWeaponModulesLootFunction.h"

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

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBaseWeaponsLootFunction>> weaponsLootFunctions;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBaseModulesLootFunction>> modulesLootFunctions;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBaseWeaponModulesLootFunction>> weaponModulesLootFunctions;

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

	const TArray<TSubclassOf<UBaseWeaponsLootFunction>>& getWeaponsLootFunctions() const;

	const TArray<TSubclassOf<UBaseModulesLootFunction>>& getModulesLootFunctions() const;

	const TArray<TSubclassOf<UBaseWeaponModulesLootFunction>>& getWeaponModulesLootFunctions() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~ULootDataAsset() = default;
};
