// Copyright (c) 2021 Use-your-imagination

#include "Constants.h"

#include "Weapons/BaseWeapon.h"
#include "AssetLoading/LostConnectionAssetManager.h"

const FRotator UConstants::rotationRate = { 0.0f, 540.0f, 0.0f };

const FString UConstants::projectVersion = "v0.2.1.0";

const FName UConstants::actionStringTablePath = "/Game/Text/Actions.Actions";
const FString UConstants::defaultActionMessageKey = "DefaultActionMessage";
const FString UConstants::actionHotkey = "ActionHotkey";

FText UConstants::getProjectVersion()
{
	return FText::FromString(UConstants::projectVersion);
}

int32 UConstants::getPersonalModulesLimit()
{
	return personalModulesLimit;
}

int32 UConstants::getWeaponModulesSize(weaponRarity rarity)
{
	switch (rarity)
	{
	case weaponRarity::normal:
		return 2;

	case weaponRarity::rare:
		return 3;

	case weaponRarity::epic:
		return 4;

	case weaponRarity::legendary:
		return 5;
	}

	return 0;
}

const FColor& UConstants::getRarityColor(weaponRarity rarity)
{
	return ULostConnectionAssetManager::get().getDefaults()[rarity];
}
