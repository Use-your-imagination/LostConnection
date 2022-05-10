// Copyright (c) 2022 Use Your Imagination

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

	void createRandomWeapon(int32 lootPoints, AInventory* playerInventory, const TArray<UBaseWeaponsLootFunction*>& lootFunctions);

	~LootCreator() = default;
};
