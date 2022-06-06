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
	/**
	* Implements IInventoriable
	*/
	UPROPERTY(Replicated)
	TObjectPtr<UNetworkObject> item;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UInventoryCell() = default;

	void setItem(IInventoriable* item);

	UFUNCTION(Category = Inventory, BlueprintCallable)
	TScriptInterface<IInventoriable> getItem() const;

	template<typename T>
	TObjectPtr<T> getItem() const;

	UFUNCTION(Category = Inventory, BlueprintCallable, Meta = (CompactDisplayName = "Is Empty"))
	bool isEmpty() const;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	~UInventoryCell() = default;
};

template<typename T>
TObjectPtr<T> UInventoryCell::getItem() const
{
	return Cast<T>(item);
}
