// Copyright (c) 2022 Use-your-imagination

#include "LootManager.h"

void ALootManager::addRandomWeapon_Implementation(UInventory* playerInventory)
{
	lootCreator.createRandomWeapon(playerInventory);
}
