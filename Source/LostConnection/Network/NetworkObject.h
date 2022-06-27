// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "NetworkObject.generated.h"

UCLASS(BlueprintType, DefaultToInstanced)
class LOSTCONNECTION_API UNetworkObject : public UObject
{
	GENERATED_BODY()
	
private:
	virtual bool IsSupportedForNetworking() const final override;

public:
	UNetworkObject() = default;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

	virtual ~UNetworkObject() = default;
};
