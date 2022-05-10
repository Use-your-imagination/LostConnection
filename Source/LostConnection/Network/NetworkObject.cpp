// Copyright (c) 2021 Use Your Imagination

#include "NetworkObject.h"

bool UNetworkObject::IsSupportedForNetworking() const
{
	return true;
}

bool UNetworkObject::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	return false;
}
