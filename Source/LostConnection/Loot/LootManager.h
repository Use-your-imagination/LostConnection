// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"

#include "LootCreator.h"

#include "LootManager.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ALootManager : public AInfo
{
	GENERATED_BODY()

private:
	LootCreator lootCreator;

public:
	ALootManager() = default;
	
	UFUNCTION(Category = Loot, Server, Reliable, BlueprintCallable)
	void addRandomWeapon(UInventory* playerInventory);

	~ALootManager() = default;
};
