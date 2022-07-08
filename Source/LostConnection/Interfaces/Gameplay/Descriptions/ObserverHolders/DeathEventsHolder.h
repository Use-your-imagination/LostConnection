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

protected:
	virtual TArray<TScriptInterface<IOnDeathEvent>>& getDeathEvents() = 0;

public:
	IDeathEventsHolder() = default;

	virtual void attachDeathEvent(TScriptInterface<IOnDeathEvent> event);

	virtual void detachDeathEvent(TScriptInterface<IOnDeathEvent> event);

	virtual void notifyDeathEvents(TObjectPtr<class ABaseCharacter> character) const;

	virtual const TArray<TScriptInterface<IOnDeathEvent>>& getDeathEvents() const;
};
