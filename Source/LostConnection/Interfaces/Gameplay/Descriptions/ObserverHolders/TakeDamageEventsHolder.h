// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnTakeDamageEvent.h"

#include "TakeDamageEventsHolder.generated.h"

UINTERFACE(BlueprintType)
class UTakeDamageEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ITakeDamageEventsHolder
{
	GENERATED_BODY()

protected:
	virtual TArray<TScriptInterface<IOnTakeDamageEvent>>& getTakeDamageEvents() = 0;

public:
	ITakeDamageEventsHolder() = default;

	virtual void attachTakeDamageEvent(TScriptInterface<IOnTakeDamageEvent> event);

	virtual void detachTakeDamageEvent(TScriptInterface<IOnTakeDamageEvent> event);

	virtual void notifyTakeDamageEvents(TScriptInterface<IDamageReceiver> receiver) const;

	virtual const TArray<TScriptInterface<IOnTakeDamageEvent>>& getTakeDamageEvents() const;
};
