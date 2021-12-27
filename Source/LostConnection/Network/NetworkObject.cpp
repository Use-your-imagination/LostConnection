// Copyright (c) 2021 Use-your-imagination

#include "NetworkObject.h"

bool UNetworkObject::IsSupportedForNetworking() const
{
	return true;
}

bool UNetworkObject::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	return false;
}
