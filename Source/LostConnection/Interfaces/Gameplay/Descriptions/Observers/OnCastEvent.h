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

public:
	IOnCastEvent() = default;

	virtual void castEventAction(const TScriptInterface<class ICaster>& caster) = 0;

	virtual TWeakInterfacePtr<class ICastEventsHolder>& getCastEventsHolder() = 0;

	virtual TScriptInterface<class ICastEventsHolder> getCastEventsHolder() const;
};
