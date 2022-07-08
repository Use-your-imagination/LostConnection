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

protected:
	virtual TArray<TScriptInterface<IOnHitEvent>>& getHitEvents() = 0;

public:
	IHitEventsHolder() = default;

	virtual void attachHitEvent(TScriptInterface<IOnHitEvent> event);

	virtual void detachHitEvent(TScriptInterface<IOnHitEvent> event);

	virtual void notifyHitEvents(TWeakObjectPtr<class ABaseCharacter> hitter, TObjectPtr<class ABaseCharacter> target) const;

	virtual const TArray<TScriptInterface<IOnHitEvent>>& getHitEvents() const;
};
