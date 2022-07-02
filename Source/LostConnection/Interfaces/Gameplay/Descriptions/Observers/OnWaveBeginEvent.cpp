// Copyright (c) 2022 Use Your Imagination

#include "OnWaveBeginEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/WaveBeginEventsHolder.h"

IWaveBeginEventsHolder* IOnWaveBeginEvent::getWaveBeginEventsHolder() const
{
	TWeakInterfacePtr<IWaveBeginEventsHolder>& holder = const_cast<IOnWaveBeginEvent*>(this)->getWaveBeginEventsHolder();

	return holder.IsValid() ? holder.Get() : nullptr;
}
