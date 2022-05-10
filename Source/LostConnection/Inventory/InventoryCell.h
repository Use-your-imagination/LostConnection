// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Network/NetworkObject.h"
#include "Interfaces/Inventory/Inventoriable.h"

#include "InventoryCell.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType)
class LOSTCONNECTION_API UInventoryCell : public UNetworkObject
{
	GENERATED_BODY()
	
private:
	/*
	* Implements IInventoriable
	*/
	UPROPERTY(Category = Inventory, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNetworkObject* item;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UInventoryCell() = default;

	void setItem(IInventoriable* item);

	IInventoriable* getItem() const;

	template<typename T>
	T* getItem() const;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~UInventoryCell() = default;
};

template<typename T>
T* UInventoryCell::getItem() const
{
	return Cast<T>(item);
}
