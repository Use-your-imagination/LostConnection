// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Inventory/Inventory.h"

class LOSTCONNECTION_API LootCreator
{
public:
	LootCreator() = default;

	void createRandomWeapon(UInventory* playerInventory);

	~LootCreator() = default;
};
