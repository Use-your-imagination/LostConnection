// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnHitEvent.h"

#include "HitEventsHolder.generated.h"

UINTERFACE(BlueprintType)
class UHitEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IHitEventsHolder
{
	GENERATED_BODY()

public:
	IHitEventsHolder() = default;

	virtual void attachHitEvent(const TScriptInterface<IOnHitEvent>& event) = 0;

	virtual void detachHitEvent(const TScriptInterface<IOnHitEvent>& event) = 0;

	virtual void notifyHitEvents() const;

	virtual const TArray<TScriptInterface<IOnHitEvent>>& getHitEvents() const = 0;
};
