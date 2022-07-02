// Copyright (c) 2022 Use Your Imagination

#include "OnHitEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/HitEventsHolder.h"

IHitEventsHolder* IOnHitEvent::getHitEventsHolder() const
{
	TWeakInterfacePtr<IHitEventsHolder>& holder = const_cast<IOnHitEvent*>(this)->getHitEventsHolder();

	return holder.IsValid() ? holder.Get() : nullptr;
}
