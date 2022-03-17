// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Utility/Enums.h"

#include "DefaultsDataAsset.generated.h"

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

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UDefaultsDataAsset();

	const TSubclassOf<class ADeathPlaceholder>& getDeathPlaceholder() const;

	const FColor& operator [] (EWeaponRarity rarity) const;

	int32 getMaxSmallAmmoCount() const;

	int32 getMaxLargeAmmoCount() const;

	int32 getMaxEnergyAmmoCount() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UDefaultsDataAsset() = default;
};
