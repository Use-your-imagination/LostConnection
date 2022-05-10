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
	UPROPERTY(Category = Placeholders, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ADeathPlaceholder> deathPlaceholder;

	UPROPERTY(Category = "UI|Weapons|Rarity", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FColor normalRarityWeaponColor;

	UPROPERTY(Category = "UI|Weapons|Rarity", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FColor rareRarityWeaponColor;

	UPROPERTY(Category = "UI|Weapons|Rarity", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FColor epicRarityWeaponColor;

	UPROPERTY(Category = "UI|Weapons|Rarity", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FColor legendaryRarityWeaponColor;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxSmallAmmoCount;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxLargeAmmoCount;

	UPROPERTY(Category = Ammo, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxEnergyAmmoCount;

	UPROPERTY(Category = WorldDefaults, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TMap<TEnumAsByte<EPhysicalSurface>, FShootThroughSurface> shootThroughSurfaces;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UDefaultsDataAsset();

	const TSubclassOf<class ADeathPlaceholder>& getDeathPlaceholder() const;

	const FColor& operator [] (EWeaponRarity rarity) const;

	const FShootThroughSurface& operator [] (const TWeakObjectPtr<UPhysicalMaterial>& physicalMaterial) const;

	int32 getMaxSmallAmmoCount() const;

	int32 getMaxLargeAmmoCount() const;

	int32 getMaxEnergyAmmoCount() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UDefaultsDataAsset() = default;
};
