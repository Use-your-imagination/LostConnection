// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Descriptions/Observers/OnWaveBeginEvent.h"

#include "WaveBeginEventsHolder.generated.h"

UINTERFACE(BlueprintType)
class UWaveBeginEventsHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWaveBeginEventsHolder
{
	GENERATED_BODY()
		
protected:
	virtual TArray<TScriptInterface<IOnWaveBeginEvent>>& getWaveBeginEvents() = 0;

public:
	IWaveBeginEventsHolder() = default;

	virtual void attachWaveBeginEvent(const TScriptInterface<IOnWaveBeginEvent>& event);

	virtual void detachWaveBeginEvent(const TScriptInterface<IOnWaveBeginEvent>& event);

	virtual void notifyWaveBeginEvents() const;

	virtual const TArray<TScriptInterface<IOnWaveBeginEvent>>& getWaveBeginEvents() const;
};
