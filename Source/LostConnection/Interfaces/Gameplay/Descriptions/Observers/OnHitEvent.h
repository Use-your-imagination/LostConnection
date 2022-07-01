// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnHitEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnHitEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnHitEvent
{
	GENERATED_BODY()

protected:
	virtual TWeakInterfacePtr<class IHitEventsHolder>& getHitEventsHolder() = 0;

public:
	IOnHitEvent() = default;

	virtual void initHitEvent(class IHitEventsHolder* holder);

	virtual void hitEventAction() = 0;

	virtual class IHitEventsHolder* getHitEventsHolder() const = 0;
};
