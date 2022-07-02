// Copyright (c) 2021 Use Your Imagination

#include "OnDeathEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/DeathEventsHolder.h"

IDeathEventsHolder* IOnDeathEvent::getDeathEventsHolder() const
{
	TWeakInterfacePtr<IDeathEventsHolder>& holder = const_cast<IOnDeathEvent*>(this)->getDeathEventsHolder();

	return holder.IsValid() ? holder.Get() : nullptr;
}
