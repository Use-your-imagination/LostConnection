// Copyright (c) 2022 Use Your Imagination

#include "OnWaveBeginEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/WaveBeginEventsHolder.h"

TScriptInterface<IWaveBeginEventsHolder> IOnWaveBeginEvent::getWaveBeginEventsHolder() const
{
	return const_cast<IOnWaveBeginEvent*>(this)->getWaveBeginEventsHolder().GetObject();
}
