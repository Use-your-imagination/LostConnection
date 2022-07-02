// Copyright (c) 2022 Use Your Imagination

#include "OnTakeDamageEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/TakeDamageEventsHolder.h"

ITakeDamageEventsHolder* IOnTakeDamageEvent::getTakeDamageEventsHolder() const
{
	TWeakInterfacePtr<ITakeDamageEventsHolder>& holder = const_cast<IOnTakeDamageEvent*>(this)->getTakeDamageEventsHolder();

	return holder.IsValid() ? holder.Get() : nullptr;
}
