// Copyright (c) 2022 Use-your-imagination

#include "InventoryCell.h"

void UInventoryCell::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryCell, item);
}

void UInventoryCell::setItem(IInventoriable* item)
{
	this->item = Cast<UNetworkObject>(item);
}

IInventoriable* UInventoryCell::getItem() const
{
	return Cast<IInventoriable>(item);
}

bool UInventoryCell::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if (IsValid(item))
	{
		wroteSomething |= Channel->ReplicateSubobject(item, *Bunch, *RepFlags);

		wroteSomething |= item->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}
