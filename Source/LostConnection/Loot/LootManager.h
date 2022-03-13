// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"

#include "LootCreator.h"
#include "AssetLoading/LostConnectionAssetManager.h"

#include "LootManager.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ALootManager : public AInfo
{
	GENERATED_BODY()

private:
	LootCreator lootCreator;

private:
	UPROPERTY(Category = Loot, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UBaseWeaponsLootFunction*> weaponsLootFunctions;

	UPROPERTY(Category = Loot, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UBaseModulesLootFunction*> modulesLootFunctions;

	UPROPERTY(Category = Loot, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UBaseWeaponModulesLootFunction*> weaponModulesLootFunctions;

private:
	void BeginPlay() override;

private:
	template<typename LootFunctionT>
	TArray<LootFunctionT*> createLootFunctions(const TArray<TSubclassOf<LootFunctionT>>& lootFunctionClasses);

	void addRandomLoot(UInventory* playerInventory, int32 weaponsLootPoints, int32 modulesLootPoints, int32 weaponModulesLootPoints);

public:
	ALootManager() = default;
	
	UFUNCTION(Category = Loot, Server, Reliable, BlueprintCallable)
	void addRandomWeapon(UInventory* playerInventory);

	const TArray<UBaseWeaponsLootFunction*>& getWeaponsLootFunctions() const;

	const TArray<UBaseModulesLootFunction*>& getModulesLootFunctions() const;

	const TArray<UBaseWeaponModulesLootFunction*>& getWeaponModulesLootFunctions() const;

	~ALootManager() = default;
};
