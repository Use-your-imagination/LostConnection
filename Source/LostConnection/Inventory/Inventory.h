// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "Network/NetworkObject.h"
#include "InventoryCell.h"
#include "Weapons/BaseWeapon.h"
#include "Utility/ReplicationStructures.h"
#include "Interfaces/Modules/Holders/PersonalModulesHolder.h"
#include "Interfaces/Modules/Holders/WeaponModulesHolder.h"

#include "Inventory.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType)
class LOSTCONNECTION_API UInventory : public UNetworkObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Player, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
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

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UInventoryCell*> unequippedWeapons;

	UPROPERTY(Category = "Inventory|Economy", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 lootPoints;

	UPROPERTY(Category = "Inventory|Ammo", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<FAmmoData> spareAmmo;

	UPROPERTY(Category = "Inventory|Modules", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UBasePersonalModule*> personalEquippedModules;

	UPROPERTY(Category = "Inventory|Modules", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UBasePersonalModule*> personalUnequippedModules;

	UPROPERTY(Category = "Inventory|Modules", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<UBaseWeaponModule*> weaponModules;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UInventory();

	void init(class ALostConnectionPlayerState* playerState);

	void addPersonalModule(UBasePersonalModule* module);

	void addWeaponModule(UBaseWeaponModule* module);

	void addUnequippedWeapon(UBaseWeapon* weapon);

	void setPrimaryWeaponCell(UBaseWeapon* weapon);

	void setSecondaryWeaponCell(UBaseWeapon* weapon);

	void setFirstInactiveWeaponCell(UBaseWeapon* weapon);

	void setSecondInactiveWeaponCell(UBaseWeapon* weapon);

	void setLootPoints(int32 lootPoints);

	UInventoryCell* getPrimaryWeaponCell() const;

	UInventoryCell* getSecondaryWeaponCell() const;

	UInventoryCell* getDefaultWeaponCell() const;

	UInventoryCell* getFirstInactiveWeaponCell() const;

	UInventoryCell* getSecondInactiveWeaponCell() const;

	int32 getLootPoints() const;

	TArray<FAmmoData>& getSpareAmmoArray();

	const TArray<UBasePersonalModule*>& getPersonalEquippedModules() const;

	const TArray<UBasePersonalModule*>& getPersonalUnequippedModules() const;

	const TArray<UBaseWeaponModule*>& getWeaponModules() const;

	class ALostConnectionPlayerState* getPlayerState() const;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~UInventory() = default;
};

inline TArray<FAmmoData>& UInventory::getSpareAmmoArray()
{
	return spareAmmo;
}
