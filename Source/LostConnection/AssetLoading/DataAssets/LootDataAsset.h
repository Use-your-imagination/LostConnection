// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "Maths/Loot/BaseWeaponsLootFunction.h"
#include "Maths/Loot/BaseModulesLootFunction.h"
#include "Maths/Loot/BaseWeaponModulesLootFunction.h"

#include "LootDataAsset.generated.h"

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FPersonalModulesCreator
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Modules, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UBasePersonalModule> brokenModule;

	UPROPERTY(Category = Modules, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UBasePersonalModule> platinumModule;
};

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FWeaponModulesCreator
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Modules, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UBaseWeaponModule> brokenModule;

	UPROPERTY(Category = Modules, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UBaseWeaponModule> platinumModule;
};

UCLASS(BlueprintType)
class LOSTCONNECTION_API ULootDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Weapons, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UBaseWeapon>> weapons;

	UPROPERTY(Category = "Modules|Personal", EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<class UBasePersonalModule>, FPersonalModulesCreator> personalModules;

	UPROPERTY(Category = "Modules|Weapon", EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<class UBaseWeaponModule>, FWeaponModulesCreator> weaponModules;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBaseWeaponsLootFunction>> weaponsLootFunctions;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBaseModulesLootFunction>> modulesLootFunctions;

	UPROPERTY(Category = LootFunctions, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBaseWeaponModulesLootFunction>> weaponModulesLootFunctions;

	UPROPERTY(Category = Coefficients, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float splitLootPointsCoefficient;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseDroppedAmmo> smallAmmoClass;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseDroppedAmmo> largeAmmoClass;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseDroppedAmmo> energyAmmoClass;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	ULootDataAsset() = default;

	TSubclassOf<class UBaseWeapon> operator [] (const TSubclassOf<class UBaseWeapon>& weapon) const;

	const TArray<TSubclassOf<class UBaseWeapon>>& getWeapons() const;

	const TMap<TSubclassOf<class UBasePersonalModule>, FPersonalModulesCreator>& getPersonalModules() const;

	const TMap<TSubclassOf<class UBaseWeaponModule>, FWeaponModulesCreator>& getWeaponModules() const;

	const TArray<TSubclassOf<UBaseWeaponsLootFunction>>& getWeaponsLootFunctions() const;

	const TArray<TSubclassOf<UBaseModulesLootFunction>>& getModulesLootFunctions() const;

	const TArray<TSubclassOf<UBaseWeaponModulesLootFunction>>& getWeaponModulesLootFunctions() const;

	float getSplitLootPointsCoefficient() const;

	const TSubclassOf<ABaseDroppedAmmo>& getSmallAmmoClass() const;

	const TSubclassOf<ABaseDroppedAmmo>& getLargeAmmoClass() const;

	const TSubclassOf<ABaseDroppedAmmo>& getEnergyAmmoClass() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~ULootDataAsset() = default;
};
