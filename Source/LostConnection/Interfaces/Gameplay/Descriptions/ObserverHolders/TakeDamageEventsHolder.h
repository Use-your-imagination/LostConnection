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

public:
	ITakeDamageEventsHolder() = default;

	virtual void attachTakeDamageEvent(const TScriptInterface<IOnTakeDamageEvent>& event) = 0;

	virtual void detachTakeDamageEvent(const TScriptInterface<IOnTakeDamageEvent>& event) = 0;

	virtual void notifyTakeDamageEvents() const;

	virtual const TArray<TScriptInterface<IOnTakeDamageEvent>>& getTakeDamageEvents() const = 0;
};
