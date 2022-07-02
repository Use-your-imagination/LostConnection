// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnShotEvent.h"

#include "ShotEventsHolder.generated.h"

UINTERFACE(BlueprintType)
class UShotEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IShotEventsHolder
{
	GENERATED_BODY()

protected:
	virtual TArray<TScriptInterface<IOnShotEvent>>& getShotEvents() = 0;

public:
	IShotEventsHolder() = default;

	virtual void attachShotEvent(const TScriptInterface<IOnShotEvent>& event);

	virtual void detachShotEvent(const TScriptInterface<IOnShotEvent>& event) ;

	virtual void notifyShotEvents() const;

	virtual const TArray<TScriptInterface<IOnShotEvent>>& getShotEvents() const ;
};
