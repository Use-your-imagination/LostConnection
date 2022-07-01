// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnDeathEvent.h"

#include "DeathEventsHolder.generated.h"

UINTERFACE(BlueprintType)
class UDeathEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDeathEventsHolder
{
	GENERATED_BODY()

public:
	virtual void attachDeathEvent(const TScriptInterface<IOnDeathEvent>& event) = 0;

	virtual void detachDeathEvent(const TScriptInterface<IOnDeathEvent>& event) = 0;

	virtual void notifyDeathEvents() const;

	virtual const TArray<TScriptInterface<IOnDeathEvent>>& getDeathEvents() const = 0;
};
