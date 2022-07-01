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

public:
	ICastEventsHolder() = default;

	virtual void attachCastEvent(const TScriptInterface<IOnCastEvent>& event) = 0;

	virtual void detachCastEvent(const TScriptInterface<IOnCastEvent>& event) = 0;

	virtual void notifyCastEvents() const;

	virtual const TArray<TScriptInterface<IOnCastEvent>>& getCastEvents() const = 0;
};
