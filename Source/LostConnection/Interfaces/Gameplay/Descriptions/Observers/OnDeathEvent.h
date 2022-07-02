// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnDeathEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnDeathEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnDeathEvent
{
	GENERATED_BODY()

public:
	IOnDeathEvent() = default;

	virtual void deathEventAction() = 0;

	virtual TWeakInterfacePtr<class IDeathEventsHolder>& getDeathEventsHolder() = 0;

	virtual class IDeathEventsHolder* getDeathEventsHolder() const;
};
