// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "Network/NetworkObject.h"
#include "InventoryCell.h"
#include "Weapons/BaseWeapon.h"

#include "Inventory.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType)
class LOSTCONNECTION_API UInventory : public UNetworkObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* primaryWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* secondaryWeaponCell;

	UPROPERTY(Category = "Inventory|Weapons", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UInventoryCell* defaultWeaponCell;

	UPROPERTY(Category = "Inventory|Economy", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int32 lootPoints;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UInventory();

	void init(APlayerState* playerState);

	void setPrimaryWeaponCell(UBaseWeapon* weapon);

	void setSecondaryWeaponCell(UBaseWeapon* weapon);

	void setLootPoints(int32 lootPoints);

	UInventoryCell* getPrimaryWeaponCell() const;

	UInventoryCell* getSecondaryWeaponCell() const;

	UInventoryCell* getDefaultWeaponCell() const;

	int32 getLootPoints() const;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~UInventory() = default;
};
