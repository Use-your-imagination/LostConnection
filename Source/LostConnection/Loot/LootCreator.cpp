// Copyright (c) 2022 Use-your-imagination

#include "LootCreator.h"

#include "AssetLoading/LostConnectionAssetManager.h"
#include "Utility/Utility.h"

void LootCreator::createRandomWeapon(UInventory* playerInventory)
{
	const TSubclassOf<UBaseWeapon>& weaponClass = Utility::getRandomValueFromArray(ULostConnectionAssetManager::get().getLoot().getWeapons());

	playerInventory->addUnequippedWeapon(NewObject<UBaseWeapon>(playerInventory->getPlayerState(), weaponClass));
}
