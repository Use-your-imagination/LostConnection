// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnHitEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnHitEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnHitEvent
{
	GENERATED_BODY()

public:
	IOnHitEvent() = default;

	virtual void hitEventAction(TWeakObjectPtr<class ABaseCharacter> hitter, TObjectPtr<class ABaseCharacter> target) = 0;

	virtual TWeakInterfacePtr<class IHitEventsHolder>& getHitEventsHolder() = 0;

	virtual TScriptInterface<class IHitEventsHolder> getHitEventsHolder() const;
};
