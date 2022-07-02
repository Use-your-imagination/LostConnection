// Copyright (c) 2022 Use Your Imagination

#include "OnShotEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/ShotEventsHolder.h"

IShotEventsHolder* IOnShotEvent::getShotEventsHolder() const
{
	TWeakInterfacePtr<IShotEventsHolder>& holder = const_cast<IOnShotEvent*>(this)->getShotEventsHolder();

	return holder.IsValid() ? holder.Get() : nullptr;
}
