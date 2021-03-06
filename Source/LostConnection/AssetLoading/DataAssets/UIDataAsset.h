// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Materials/Material.h"

#include "UI/LostConnectionUI.h"
#include "UI/InventoryWidget.h"

#include "UIDataAsset.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UUIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<ULostConnectionUI> defaultUI;

	UPROPERTY(Category = UI, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> defaultDeathUI;

	UPROPERTY(Category = "UI|Widgets", EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<UInventoryWidget> inventoryWidget;

	UPROPERTY(Category = Materials, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	UMaterial* baseWeaponSelectorMaterial;

public:
	static FPrimaryAssetId getPrimaryAssetId();

public:
	UUIDataAsset() = default;

	const TSubclassOf<ULostConnectionUI>& getDefaultUI() const;

	const TSubclassOf<UUserWidget>& getDefaultDeathUI() const;

	const TSubclassOf<UInventoryWidget>& getInventoryWidget() const;

	UMaterial* getBaseWeaponSelectorMaterial() const;

	FPrimaryAssetId GetPrimaryAssetId() const override;

	~UUIDataAsset() = default;
};
