// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnCastEvent.h"

#include "CastEventsHolder.generated.h"

UINTERFACE(BlueprintType)
class UCastEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ICastEventsHolder
{
	GENERATED_BODY()

protected:
	virtual TArray<TScriptInterface<IOnCastEvent>>& getCastEvents() = 0;

public:
	ICastEventsHolder() = default;

	virtual void attachCastEvent(TScriptInterface<IOnCastEvent> event);

	virtual void detachCastEvent(TScriptInterface<IOnCastEvent> event);

	virtual void notifyCastEvents(TScriptInterface<class ICaster> caster) const;

	virtual const TArray<TScriptInterface<IOnCastEvent>>& getCastEvents() const;
};
