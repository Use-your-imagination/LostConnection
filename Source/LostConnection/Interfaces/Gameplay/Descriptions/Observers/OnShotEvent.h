// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnShotEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnShotEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnShotEvent
{
	GENERATED_BODY()

protected:
	virtual TWeakInterfacePtr<class IShotEventsHolder>& getShotEventsHolder() = 0;

public:
	IOnShotEvent() = default;

	virtual void initShotEvent(class IShotEventsHolder* holder);

	virtual void shotEventAction() = 0;

	virtual class IShotEventsHolder* getShotEventsHolder() const = 0;
};
