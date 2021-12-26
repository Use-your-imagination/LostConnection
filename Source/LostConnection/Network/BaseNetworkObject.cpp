// Copyright (c) 2021 Use-your-imagination

#include "BaseNetworkObject.h"

bool UBaseNetworkObject::IsSupportedForNetworking() const
{
	return true;
}

bool UBaseNetworkObject::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	return false;
}
