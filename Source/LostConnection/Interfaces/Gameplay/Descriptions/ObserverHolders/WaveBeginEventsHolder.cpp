// Copyright (c) 2022 Use Your Imagination

#include "WaveBeginEventsHolder.h"

void IWaveBeginEventsHolder::attachWaveBeginEvent(const TScriptInterface<IOnWaveBeginEvent>& event)
{
	auto& currentHolder = event->getWaveBeginEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachWaveBeginEvent(event.GetObject());
	}

	currentHolder = this;

	this->getWaveBeginEvents().Add(event);
}

void IWaveBeginEventsHolder::detachWaveBeginEvent(const TScriptInterface<IOnWaveBeginEvent>& event)
{
	this->getWaveBeginEvents().RemoveSingle(event);
}

void IWaveBeginEventsHolder::notifyWaveBeginEvents() const
{
	for (const auto& event : this->getWaveBeginEvents())
	{
		event->waveBeginEventAction();
	}
}

const TArray<TScriptInterface<IOnWaveBeginEvent>>& IWaveBeginEventsHolder::getWaveBeginEvents() const
{
	return const_cast<IWaveBeginEventsHolder*>(this)->getWaveBeginEvents();
}
