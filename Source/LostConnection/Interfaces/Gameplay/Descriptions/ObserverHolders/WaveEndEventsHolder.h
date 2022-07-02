// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnWaveEndEvent.h"

#include "WaveEndEventsHolder.generated.h"

UINTERFACE(BlueprintType)
class UWaveEndEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWaveEndEventsHolder
{
	GENERATED_BODY()

protected:
	virtual TArray<TScriptInterface<IOnWaveEndEvent>>& getWaveEndEvents() = 0;

public:
	IWaveEndEventsHolder() = default;

	virtual void attachWaveEndEvent(const TScriptInterface<IOnWaveEndEvent>& event);

	virtual void detachWaveEndEvent(const TScriptInterface<IOnWaveEndEvent>& event);

	virtual void notifyWaveEndEvents() const;

	virtual const TArray<TScriptInterface<IOnWaveEndEvent>>& getWaveEndEvents() const;
};
