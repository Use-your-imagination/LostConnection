// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"

#include "Network/NetworkObject.h"
#include "InventoryCell.h"
#include "Weapons/BaseWeapon.h"

#include "Inventory.generated.h"

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

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UInventory();

	void init(APlayerState* playerState);

	UFUNCTION(Server, Reliable)
	void setPrimaryWeaponCell(UBaseWeapon* weapon);

	UFUNCTION(Server, Reliable)
	void setSecondaryWeaponCell(UBaseWeapon* weapon);

	UInventoryCell* getPrimaryWeaponCell() const;

	UInventoryCell* getSecondaryWeaponCell() const;

	UInventoryCell* getDefaultWeaponCell() const;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~UInventory() = default;
};
