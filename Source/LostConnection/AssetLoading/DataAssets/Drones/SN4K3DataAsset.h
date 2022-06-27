// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "AssetLoading/DataAssets/Drones/BaseDroneDataAsset.h"

#include "SN4K3DataAsset.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3DataAsset : public UBaseDroneDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> headUI;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASN4K3UltimateAbilityPlaceholder> ultimateAbilityPlaceholder;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASN4K3ThirdAbilityFlag> thirdAbilityFlag;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	USN4K3DataAsset() = default;

	const TSubclassOf<UUserWidget>& getHeadUI() const;

	const TSubclassOf<class ASN4K3UltimateAbilityPlaceholder>& getUltimateAbilityPlaceholder() const;

	const TSubclassOf<class ASN4K3ThirdAbilityFlag>& getThirdAbilityFlag() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~USN4K3DataAsset() = default;
};
