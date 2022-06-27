// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include "Utility/Enums.h"

#include "DefaultsDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FShootThroughSurface
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = ShotThrough, EditDefaultsOnly, BlueprintReadOnly)
	float flatDamageReducation;

	UPROPERTY(Category = ShotThrough, EditDefaultsOnly, BlueprintReadOnly)
	float percentDamageReduction;

	FShootThroughSurface();
};

UCLASS(BlueprintType)
class LOSTCONNECTION_API UDefaultsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Placeholders, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<class ADeathPlaceholder> deathPlaceholder;

	UPROPERTY(Category = "UI|Weapons|Rarity", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TMap<EWeaponRarity, FLinearColor> weaponsRarityColor;

	UPROPERTY(Category = "UI|Modules|Quality", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TMap<EModuleQuality, FLinearColor> modulesQualityColor;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 maxSmallAmmoCount;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 maxLargeAmmoCount;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 maxEnergyAmmoCount;

	UPROPERTY(Category = WorldDefaults, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TMap<TEnumAsByte<EPhysicalSurface>, FShootThroughSurface> shootThroughSurfaces;

	UPROPERTY(Category = GameDefaults, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float resistHardcap;

	UPROPERTY(Category = GameDefaults, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 modulesToNextTier;

	UPROPERTY(Category = GameDefaults, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 maxSpendLootPoints;

	UPROPERTY(Category = WeaponDefaults, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float maxShootDistance;

	UPROPERTY(Category = CharacterDefaults, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 personalModulesLimit;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UDefaultsDataAsset();

	const TSubclassOf<class ADeathPlaceholder>& getDeathPlaceholder() const;

	const FLinearColor& operator [] (EWeaponRarity rarity) const;

	const FLinearColor& operator [] (EModuleQuality quality) const;

	const FShootThroughSurface& operator [] (const TWeakObjectPtr<UPhysicalMaterial>& physicalMaterial) const;

	int32 getMaxSmallAmmoCount() const;

	int32 getMaxLargeAmmoCount() const;

	int32 getMaxEnergyAmmoCount() const;

	float getResistHardcap() const;

	int32 getModulesToNextTier() const;

	int32 getMaxSpendLootPoints() const;

	int32 getMaxShootDistance() const;

	int32 getPersonalModulesLimit() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UDefaultsDataAsset() = default;
};
