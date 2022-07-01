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

protected:
	virtual TWeakInterfacePtr<class IWaveBeginEventsHolder>& getWaveBeginEventsHolder() = 0;

public:
	IOnWaveBeginEvent() = default;

	virtual void initWaveBeginEvent(class IWaveBeginEventsHolder* holder);

	virtual void waveBeginEventAction() = 0;

	virtual class IWaveBeginEventsHolder* getWaveBeginEventsHolder() const = 0;
};
