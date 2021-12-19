// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Materials/Material.h"

#include "UIDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UUIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> defaultUI;

	UPROPERTY(Category = Materials, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UMaterial* baseWeaponSelectorMaterial;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UUIDataAsset() = default;

	const TSubclassOf<UUserWidget>& getDefaultUI() const;

	UMaterial* getBaseWeaponSelectorMaterial() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual ~UUIDataAsset() = default;
};
