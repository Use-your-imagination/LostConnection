// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "OnShotEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnShotEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnShotEvent
{
	GENERATED_BODY()

public:
	IOnShotEvent() = default;

	virtual void shotEventAction(TScriptInterface<IDamageInflictor> inflictor) = 0;

	virtual TWeakInterfacePtr<class IShotEventsHolder>& getShotEventsHolder() = 0;

	virtual TScriptInterface<class IShotEventsHolder> getShotEventsHolder() const;
};
