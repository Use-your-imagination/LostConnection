// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "OnDeathEvent.generated.h"

UINTERFACE(MinimalAPI)
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

	virtual class IDeathEventsHolder* getDeathEventsHolder() const = 0;
};
