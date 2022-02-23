// Copyright (c) 2021 Use-your-imagination

#include "SN4K3DataAsset.h"

#include "WorldPlaceables/SN4K3/SN4K3UltimateAbilityPlaceholder.h"
#include "WorldPlaceables/SN4K3/SN4K3ThirdAbilityFlag.h"

FPrimaryAssetId USN4K3DataAsset::getPrimaryAssetId()
{
	return FPrimaryAssetId(USN4K3DataAsset::getPrimaryAssetType(), "SN4K3");
}

const TSubclassOf<UUserWidget>& USN4K3DataAsset::getHeadUI() const
{
	return headUI;
}

const TSubclassOf<ASN4K3UltimateAbilityPlaceholder>& USN4K3DataAsset::getUltimateAbilityPlaceholder() const
{
	return ultimateAbilityPlaceholder;
}

const TSubclassOf<ASN4K3ThirdAbilityFlag>& USN4K3DataAsset::getThirdAbilityFlag() const
{
	return thirdAbilityFlag;
}

FPrimaryAssetId USN4K3DataAsset::GetPrimaryAssetId() const
{
	return USN4K3DataAsset::getPrimaryAssetId();
}
