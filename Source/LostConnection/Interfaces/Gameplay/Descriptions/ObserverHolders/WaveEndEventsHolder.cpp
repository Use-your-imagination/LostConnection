// Copyright (c) 2022 Use Your Imagination

#include "WaveEndEventsHolder.h"

void IWaveEndEventsHolder::attachWaveEndEvent(const TScriptInterface<IOnWaveEndEvent>& event)
{
	auto& currentHolder = event->getWaveEndEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachWaveEndEvent(event.GetObject());
	}

	currentHolder = this;

	this->getWaveEndEvents().Add(event);
}

void IWaveEndEventsHolder::detachWaveEndEvent(const TScriptInterface<IOnWaveEndEvent>& event)
{
	this->getWaveEndEvents().RemoveSingle(event);
}

void IWaveEndEventsHolder::notifyWaveEndEvents() const
{
	for (const auto& event : this->getWaveEndEvents())
	{
		event->waveEndEventAction();
	}
}

const TArray<TScriptInterface<IOnWaveEndEvent>>& IWaveEndEventsHolder::getWaveEndEvents() const
{
	return const_cast<IWaveEndEventsHolder*>(this)->getWaveEndEvents();
}
