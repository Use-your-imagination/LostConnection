// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnWaveBeginEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnWaveBeginEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnWaveBeginEvent
{
	GENERATED_BODY()

public:
	IOnWaveBeginEvent() = default;

	virtual void waveBeginEventAction(TObjectPtr<UWorld> world) = 0;

	virtual TWeakInterfacePtr<class IWaveBeginEventsHolder>& getWaveBeginEventsHolder() = 0;

	virtual TScriptInterface<class IWaveBeginEventsHolder> getWaveBeginEventsHolder() const;
};
