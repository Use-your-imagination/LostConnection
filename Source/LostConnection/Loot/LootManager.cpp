// Copyright (c) 2022 Use-your-imagination

#include "LootManager.h"

#include "Engine/LostConnectionPlayerState.h"
#include "Constants/Constants.h"

void ALootManager::addRandomWeapon_Implementation(UInventory* playerInventory)
{
	playerInventory->getPlayerState()->spendLootPoints(FMath::Min(playerInventory->getLootPoints(), UConstants::maxSpendLootPoints));

	lootCreator.createRandomWeapon(playerInventory);
}
