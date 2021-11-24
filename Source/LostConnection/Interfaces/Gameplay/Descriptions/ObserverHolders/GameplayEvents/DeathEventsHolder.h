// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "Interfaces/Gameplay/Descriptions/Observers/GameplayEvents/OnDeathEvent.h"

#include "DeathEventsHolder.generated.h"

UINTERFACE(MinimalAPI)
class UDeathEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDeathEventsHolder
{
	GENERATED_BODY()

public:
	virtual void attachDeathEvent(IOnDeathEvent* event) = 0;

	virtual void detachDeathEvent(IOnDeathEvent* event) = 0;

	virtual void notifyDeathEvents() const;

	virtual const TArray<TWeakInterfacePtr<IOnDeathEvent>>& getDeathEvents() const = 0;
};
