// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "UObject/WeakInterfacePtr.h"

#include "OnWaveEndEvent.generated.h"

UINTERFACE(BlueprintType)
class UOnWaveEndEvent : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IOnWaveEndEvent
{
	GENERATED_BODY()

protected:
	virtual TWeakInterfacePtr<class IWaveEndEventsHolder>& getWaveEndEventsHolder() = 0;

public:
	IOnWaveEndEvent() = default;

	virtual void initWaveEndEvent(class IWaveEndEventsHolder* holder);

	virtual void waveEndEventAction() = 0;

	virtual class IWaveEndEventsHolder* getWaveEndEventsHolder() const = 0;
};
