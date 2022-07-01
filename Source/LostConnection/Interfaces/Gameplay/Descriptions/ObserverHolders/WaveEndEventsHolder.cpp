// Copyright (c) 2022 Use Your Imagination

#include "WaveEndEventsHolder.h"

void IWaveEndEventsHolder::notifyWaveEndEvents() const
{
	for (const auto& event : this->getWaveEndEvents())
	{
		event->waveEndEventAction();
	}
}
