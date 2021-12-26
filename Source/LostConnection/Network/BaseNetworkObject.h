// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Net/UnrealNetwork.h"

#include "BaseNetworkObject.generated.h"

UCLASS(BlueprintType)
class LOSTCONNECTION_API UBaseNetworkObject : public UObject
{
	GENERATED_BODY()
	
private:
	virtual bool IsSupportedForNetworking() const final override;

public:
	UBaseNetworkObject() = default;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

	virtual ~UBaseNetworkObject() = default;
};
