// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageReceiver.h"

#include "OnTakeDamageEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnTakeDamageEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnTakeDamageEvent
{
	GENERATED_BODY()

public:
	IOnTakeDamageEvent() = default;

	virtual void takeDamageEventAction(TScriptInterface<IDamageReceiver> receiver) = 0;

	virtual TWeakInterfacePtr<class ITakeDamageEventsHolder>& getTakeDamageEventsHolder() = 0;

	virtual TScriptInterface<class ITakeDamageEventsHolder> getTakeDamageEventsHolder() const;
};
