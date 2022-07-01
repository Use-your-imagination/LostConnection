// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnCastEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnCastEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnCastEvent
{
	GENERATED_BODY()

protected:
	virtual TWeakInterfacePtr<class ICastEventsHolder>& getCastEventsHolder() = 0;

public:
	IOnCastEvent() = default;

	virtual void initCastEvent(class ICastEventsHolder* holder);

	virtual void castEventAction() = 0;

	virtual class ICastEventsHolder* getCastEventsHolder() const = 0;
};
