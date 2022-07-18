// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Info.h"

#include "InventoryCell.h"
#include "Weapons/BaseWeapon.h"
#include "Utility/ReplicationStructures.h"
#include "Interfaces/Modules/Holders/PersonalModulesHolder.h"
#include "Interfaces/Modules/Holders/WeaponModulesHolder.h"

#include "Inventory.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType)
class LOSTCONNECTION_API AInventory : public AInfo
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Player, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<class ALostConnectionPlayerState> playerState;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UInventoryCell> primaryWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UInventoryCell> secondaryWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UInventoryCell> defaultWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UInventoryCell> firstInactiveWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UInventoryCell> secondInactiveWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", ReplicatedUsing = onInventoryUpdate, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TArray<TObjectPtr<UInventoryCell>> unequippedWeapons;

	UPROPERTY(Category = "Inventory|Economy", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 lootPoints;

	UPROPERTY(Category = "Inventory|Ammo", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TArray<FAmmoData> spareAmmo;

	UPROPERTY(Category = "Inventory|Modules", ReplicatedUsing = onInventoryUpdate, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TArray<TObjectPtr<UInventoryCell>> equippedPersonalModules;

	UPROPERTY(Category = "Inventory|Modules", ReplicatedUsing = onInventoryUpdate, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TArray<TObjectPtr<UInventoryCell>> unequippedPersonalModules;

	UPROPERTY(Category = "Inventory|Modules", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TArray<TObjectPtr<UInventoryCell>> weaponModules;

	UPROPERTY(Category = "Inventory|Defaults", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 maxSmallAmmoCount;

	UPROPERTY(Category = "Inventory|Defaults", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 maxLargeAmmoCount;

	UPROPERTY(Category = "Inventory|Defaults", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	int32 maxEnergyAmmoCount;

	/**
	* Unequipped personal modules
	* Same type as equipped modules
	*/
	UPROPERTY()
	TArray<TObjectPtr<UInventoryCell>> activePersonalModules;

	/**
	* Unequipped weapon modules 
	* Same type as equipped modules
	*/
	UPROPERTY()
	TArray<TObjectPtr<UInventoryCell>> activeWeaponModules;

private:
	void updateActivePersonalModules();

	bool swapBetweenUnequippedWeaponsAndSlot(TObjectPtr<UInventoryCell>& slot, UBaseWeapon* weapon);

	TArray<TObjectPtr<UInventoryCell>> upgradeModules(const TArray<TObjectPtr<UInventoryCell>*>& modules);

	void upgradeModule(TObjectPtr<UInventoryCell> moduleToUpgrade);

	UFUNCTION()
	void onInventoryUpdate();

	UFUNCTION(NetMulticast, Reliable)
	void updateInventoryWidget();

private:
	static bool containsItem(TObjectPtr<UInventoryCell> itemToFind, const TArray<TObjectPtr<UInventoryCell>>& cells);

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	AInventory();

	void init(TObjectPtr<class ALostConnectionPlayerState> playerState);

	void updateActiveWeaponModules();

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void equipOrUnequipPersonalModule(UInventoryCell* module);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void swapPersonalModules(UInventoryCell* firstModule, UInventoryCell* secondModule);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void equipOrUnequipWeaponModule(UInventoryCell* selectedWeapon, UInventoryCell* module);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void swapWeaponModules(UInventoryCell* selectedWeapon, UInventoryCell* firstModule, UInventoryCell* secondModule);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void addPersonalModule(UBasePersonalModule* module);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void addWeaponModule(UBaseWeaponModule* module);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void addUnequippedWeapon(UBaseWeapon* weapon);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void setPrimaryWeaponCell(UBaseWeapon* weapon);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void setSecondaryWeaponCell(UBaseWeapon* weapon);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void setFirstInactiveWeaponCell(UBaseWeapon* weapon);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void setSecondInactiveWeaponCell(UBaseWeapon* weapon);

	UFUNCTION(Category = Inventory, Server, Reliable, BlueprintCallable)
	void setLootPoints(int32 newLootPoints);

	UFUNCTION(Server, Reliable)
	void setMaxSmallAmmoCount(int32 count);

	UFUNCTION(Server, Reliable)
	void setMaxLargeAmmoCount(int32 count);

	UFUNCTION(Server, Reliable)
	void setMaxEnergyAmmoCount(int32 count);

	TObjectPtr<UInventoryCell> getPrimaryWeaponCell() const;

	TObjectPtr<UInventoryCell> getSecondaryWeaponCell() const;

	TObjectPtr<UInventoryCell> getDefaultWeaponCell() const;

	TObjectPtr<UInventoryCell> getFirstInactiveWeaponCell() const;

	TObjectPtr<UInventoryCell> getSecondInactiveWeaponCell() const;

	int32 getLootPoints() const;

	TArray<FAmmoData>& getSpareAmmoArray();

	const TArray<TObjectPtr<UInventoryCell>>& getPersonalEquippedModules() const;

	const TArray<TObjectPtr<UInventoryCell>>& getPersonalUnequippedModules() const;

	const TArray<TObjectPtr<UInventoryCell>>& getWeaponModules() const;

	TObjectPtr<class ALostConnectionPlayerState> getPlayerState() const;

	int32 getMaxSmallAmmoCount() const;

	int32 getMaxLargeAmmoCount() const;

	int32 getMaxEnergyAmmoCount() const;

	int32 getMaxAmmoCount(EAmmoType type) const;

	const TArray<TObjectPtr<UInventoryCell>>& getActivePersonalModules() const;

	const TArray<TObjectPtr<UInventoryCell>>& getActiveWeaponModules() const;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~AInventory() = default;
};

inline TArray<FAmmoData>& AInventory::getSpareAmmoArray()
{
	return spareAmmo;
}
