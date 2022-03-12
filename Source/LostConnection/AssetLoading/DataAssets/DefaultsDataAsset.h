// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "DefaultsDataAsset.generated.h"

enum class weaponRarity : uint8;

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

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UDefaultsDataAsset() = default;

	const TSubclassOf<class ADeathPlaceholder>& getDeathPlaceholder() const;

	const FColor& operator [] (weaponRarity rarity) const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UDefaultsDataAsset() = default;
};
