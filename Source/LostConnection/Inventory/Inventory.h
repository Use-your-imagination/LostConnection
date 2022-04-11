// Copyright (c) 2022 Use-your-imagination

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
	UPROPERTY(Category = Player, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	class ALostConnectionPlayerState* playerState;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* primaryWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* secondaryWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* defaultWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* firstInactiveWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* secondInactiveWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", ReplicatedUsing = onUnequippedWeaponsUpdate, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UInventoryCell*> unequippedWeapons;

	UPROPERTY(Category = "Inventory|Economy", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 lootPoints;

	UPROPERTY(Category = "Inventory|Ammo", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<FAmmoData> spareAmmo;

	UPROPERTY(Category = "Inventory|Modules", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UInventoryCell*> personalEquippedModules;

	UPROPERTY(Category = "Inventory|Modules", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UInventoryCell*> personalUnequippedModules;

	UPROPERTY(Category = "Inventory|Modules", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UInventoryCell*> weaponModules;

	UPROPERTY(Category = "Inventory|Defaults", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxSmallAmmoCount;

	UPROPERTY(Category = "Inventory|Defaults", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxLargeAmmoCount;

	UPROPERTY(Category = "Inventory|Defaults", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxEnergyAmmoCount;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool swapBetweenUnequippedWeaponsAndSlot(UInventoryCell*& slot, UBaseWeapon* weapon);

	UFUNCTION()
	void onUnequippedWeaponsUpdate();

public:
	AInventory();

	void init(class ALostConnectionPlayerState* playerState);

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

	UInventoryCell* getPrimaryWeaponCell() const;

	UInventoryCell* getSecondaryWeaponCell() const;

	UInventoryCell* getDefaultWeaponCell() const;

	UInventoryCell* getFirstInactiveWeaponCell() const;

	UInventoryCell* getSecondInactiveWeaponCell() const;

	int32 getLootPoints() const;

	TArray<FAmmoData>& getSpareAmmoArray();

	const TArray<UInventoryCell*>& getPersonalEquippedModules() const;

	const TArray<UInventoryCell*>& getPersonalUnequippedModules() const;

	const TArray<UInventoryCell*>& getWeaponModules() const;

	class ALostConnectionPlayerState* getPlayerState() const;

	int32 getMaxSmallAmmoCount() const;

	int32 getMaxLargeAmmoCount() const;

	int32 getMaxEnergyAmmoCount() const;

	int32 getMaxAmmoCount(EAmmoType type) const;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~AInventory() = default;
};

inline TArray<FAmmoData>& AInventory::getSpareAmmoArray()
{
	return spareAmmo;
}
