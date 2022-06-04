// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"

#include "LootCreator.h"
#include "AssetLoading/LostConnectionAssetManager.h"
#include "Interfaces/Loot/AmmoDropable.h"

#include "LootManager.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API ALootManager : public AInfo
{
	GENERATED_BODY()

private:
	LootCreator lootCreator;

private:
	UPROPERTY(Category = Loot, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UBaseWeaponsLootFunction>> weaponsLootFunctions;

	UPROPERTY(Category = Loot, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UBaseModulesLootFunction>> modulesLootFunctions;

	UPROPERTY(Category = Loot, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UBaseWeaponModulesLootFunction>> weaponModulesLootFunctions;

private:
	void BeginPlay() override;

private:
	template<typename LootFunctionT>
	TArray<TObjectPtr<LootFunctionT>> createLootFunctions(const TArray<TSubclassOf<LootFunctionT>>& lootFunctionClasses);

	void addRandomLoot(AInventory* playerInventory, int32 weaponsLootPoints, int32 modulesLootPoints, int32 weaponModulesLootPoints);

	UFUNCTION(Client, Reliable)
	void spawnAmmo(UObject* ammoDropable);

public:
	ALootManager();

	UFUNCTION(Server, Reliable)
	void init(APlayerController* playerController);
	
	UFUNCTION(Category = Loot, Server, Reliable, BlueprintCallable)
	void addRandomWeapon(AInventory* playerInventory);

	UFUNCTION(Category = Loot, Server, Reliable, BlueprintCallable)
	void addRandomModule(AInventory* playerInventory);

	UFUNCTION(Category = Loot, Server, Reliable, BlueprintCallable)
	void addRandomWeaponModule(AInventory* playerInventory);

	UFUNCTION(Category = Loot, BlueprintCallable)
	void spawnAmmoCall(TScriptInterface<IAmmoDropable> ammoDropable);

	const TArray<UBaseWeaponsLootFunction*>& getWeaponsLootFunctions() const;

	const TArray<UBaseModulesLootFunction*>& getModulesLootFunctions() const;

	const TArray<UBaseWeaponModulesLootFunction*>& getWeaponModulesLootFunctions() const;

	~ALootManager() = default;
};
