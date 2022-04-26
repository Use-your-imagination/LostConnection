// Copyright (c) 2021 Use-your-imagination

#include "Constants.h"

#include "Misc/NetworkVersion.h"

#include "Weapons/BaseWeapon.h"
#include "AssetLoading/LostConnectionAssetManager.h"

const FRotator UConstants::rotationRate = { 0.0f, 540.0f, 0.0f };

const FName UConstants::actionStringTablePath = "/Game/Text/Actions.Actions";
const FString UConstants::defaultActionMessageKey = "DefaultActionMessage";
const FString UConstants::actionHotkey = "ActionHotkey";

FText UConstants::getProjectVersion()
{
	return FText::FromString(FNetworkVersion::GetProjectVersion());
}

int32 UConstants::getPersonalModulesLimit()
{
	return personalModulesLimit;
}

int32 UConstants::getWeaponModulesSize(EWeaponRarity rarity)
{
	switch (rarity)
	{
	case EWeaponRarity::normal:
		return 2;

	case EWeaponRarity::rare:
		return 3;

	case EWeaponRarity::epic:
		return 4;

	case EWeaponRarity::legendary:
		return 5;
	}

	return 0;
}

const FColor& UConstants::getRarityColor(EWeaponRarity rarity)
{
	return ULostConnectionAssetManager::get().getDefaults()[rarity];
}
