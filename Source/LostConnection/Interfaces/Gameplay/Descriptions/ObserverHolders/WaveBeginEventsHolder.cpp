// Copyright (c) 2022 Use Your Imagination

#include "WaveBeginEventsHolder.h"

void IWaveBeginEventsHolder::notifyWaveBeginEvents() const
{
	for (const auto& event : this->getWaveBeginEvents())
	{
		event->waveBeginEventAction();
	}
}
