// Copyright (c) 2022 Use Your Imagination

#include "WaveBeginEventsHolder.h"

void IWaveBeginEventsHolder::attachWaveBeginEvent(TScriptInterface<IOnWaveBeginEvent> event)
{
	auto& currentHolder = event->getWaveBeginEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachWaveBeginEvent(event.GetObject());
	}

	currentHolder = this;

	this->getWaveBeginEvents().Add(event);
}

void IWaveBeginEventsHolder::detachWaveBeginEvent(TScriptInterface<IOnWaveBeginEvent> event)
{
	this->getWaveBeginEvents().RemoveSingle(event);
}

void IWaveBeginEventsHolder::notifyWaveBeginEvents(TObjectPtr<UWorld> world) const
{
	for (const auto& event : this->getWaveBeginEvents())
	{
		event->waveBeginEventAction(world);
	}
}

const TArray<TScriptInterface<IOnWaveBeginEvent>>& IWaveBeginEventsHolder::getWaveBeginEvents() const
{
	return const_cast<IWaveBeginEventsHolder*>(this)->getWaveBeginEvents();
}
