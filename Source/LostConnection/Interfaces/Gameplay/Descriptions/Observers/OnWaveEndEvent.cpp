// Copyright (c) 2022 Use Your Imagination

#include "OnWaveEndEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/WaveEndEventsHolder.h"

IWaveEndEventsHolder* IOnWaveEndEvent::getWaveEndEventsHolder() const
{
	TWeakInterfacePtr<IWaveEndEventsHolder>& holder = const_cast<IOnWaveEndEvent*>(this)->getWaveEndEventsHolder();

	return holder.IsValid() ? holder.Get() : nullptr;
}
