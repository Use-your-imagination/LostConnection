// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Inventory/Inventory.h"
#include "Maths/Loot/BaseWeaponsLootFunction.h"
#include "Maths/Loot/BaseModulesLootFunction.h"
#include "Maths/Loot/BaseWeaponModulesLootFunction.h"

class LOSTCONNECTION_API LootCreator
{
public:
	LootCreator() = default;

	void createRandomWeapon(int32 lootPoints, UInventory* playerInventory, const TArray<UBaseWeaponsLootFunction*>& lootFunctions);

	~LootCreator() = default;
};
