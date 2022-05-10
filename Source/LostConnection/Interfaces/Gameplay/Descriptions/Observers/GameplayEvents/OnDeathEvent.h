// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnDeathEvent.generated.h"

UINTERFACE(MinimalAPI)
class UOnDeathEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnDeathEvent
{
	GENERATED_BODY()

protected:
	virtual TWeakInterfacePtr<class IDeathEventsHolder>& getDeathEventsHolder() = 0;

public:
	IOnDeathEvent() = default;

	virtual void initDeathEvent(class IDeathEventsHolder* holder);

	virtual void deathEventAction() = 0;

	virtual class IDeathEventsHolder* getDeathEventsHolder() const = 0;
};
