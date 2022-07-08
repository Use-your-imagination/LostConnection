// Copyright (c) 2022 Use Your Imagination

#include "OnWaveEndEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/WaveEndEventsHolder.h"

TScriptInterface<IWaveEndEventsHolder> IOnWaveEndEvent::getWaveEndEventsHolder() const
{
	return const_cast<IOnWaveEndEvent*>(this)->getWaveEndEventsHolder().GetObject();
}
