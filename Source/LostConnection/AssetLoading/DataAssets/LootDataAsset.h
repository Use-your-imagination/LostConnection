// Copyright (c) 2022 Use Your Imagination

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
	UPROPERTY(Category = Weapons, EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<TSubclassOf<class UBaseWeapon>> weapons;

	/**
	* Module class - Platinum module class
	*/
	UPROPERTY(Category = "Modules|Personal", EditDefaultsOnly, Meta = (AllowPrivateAccess, AllowAbstract = "false"))
	TMap<TSubclassOf<class UBasePersonalModule>, TSubclassOf<class UBasePersonalModule>> personalModules;

	/**
	* Weapon module class - Platinum weapon module class
	*/
	UPROPERTY(Category = "Modules|Weapon", EditDefaultsOnly, Meta = (AllowPrivateAccess, AllowAbstract = "false"))
	TMap<TSubclassOf<class UBaseWeaponModule>, TSubclassOf<class UBaseWeaponModule>> weaponModules;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UBaseWeaponsLootFunction>> weaponsLootFunctions;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UBaseModulesLootFunction>> modulesLootFunctions;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<TSubclassOf<UBaseWeaponModulesLootFunction>> weaponModulesLootFunctions;

	UPROPERTY(Category = Coefficients, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float splitLootPointsCoefficient;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<class ABaseDroppedAmmo> smallAmmoClass;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<class ABaseDroppedAmmo> largeAmmoClass;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<class ABaseDroppedAmmo> energyAmmoClass;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	ULootDataAsset() = default;

	TSubclassOf<class UBaseWeapon> operator [] (const TSubclassOf<class UBaseWeapon>& weapon) const;

	const TArray<TSubclassOf<class UBaseWeapon>>& getWeapons() const;

	const TMap<TSubclassOf<class UBasePersonalModule>, TSubclassOf<class UBasePersonalModule>>& getPersonalModules() const;

	const TMap<TSubclassOf<class UBaseWeaponModule>, TSubclassOf<class UBaseWeaponModule>>& getWeaponModules() const;

	const TArray<TSubclassOf<UBaseWeaponsLootFunction>>& getWeaponsLootFunctions() const;

	const TArray<TSubclassOf<UBaseModulesLootFunction>>& getModulesLootFunctions() const;

	const TArray<TSubclassOf<UBaseWeaponModulesLootFunction>>& getWeaponModulesLootFunctions() const;

	float getSplitLootPointsCoefficient() const;

	const TSubclassOf<ABaseDroppedAmmo>& getSmallAmmoClass() const;

	const TSubclassOf<ABaseDroppedAmmo>& getLargeAmmoClass() const;

	const TSubclassOf<ABaseDroppedAmmo>& getEnergyAmmoClass() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~ULootDataAsset() = default;
};
