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

public:
	IOnShotEvent() = default;

	virtual void shotEventAction() = 0;

	virtual TWeakInterfacePtr<class IShotEventsHolder>& getShotEventsHolder() = 0;

	virtual class IShotEventsHolder* getShotEventsHolder() const;
};
