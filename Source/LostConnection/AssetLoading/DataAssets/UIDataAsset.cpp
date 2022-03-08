// Copyright (c) 2021 Use-your-imagination


#include "UIDataAsset.h"

FPrimaryAssetId UUIDataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(FPrimaryAssetType("UI"), "UI");
}

const TSubclassOf<ULostConnectionUI>& UUIDataAsset::getDefaultUI() const
{
	return defaultUI;
}

const TSubclassOf<UUserWidget>& UUIDataAsset::getDefaultDeathUI() const
{
	return defaultDeathUI;
}

const TSubclassOf<UInventoryWidget>& UUIDataAsset::getInventoryWidget() const
{
	return inventoryWidget;
}

UMaterial* UUIDataAsset::getBaseWeaponSelectorMaterial() const
{
	return baseWeaponSelectorMaterial;
}

FPrimaryAssetId UUIDataAsset::GetPrimaryAssetId() const
{
	return UUIDataAsset::getPrimaryAssetId();
}
