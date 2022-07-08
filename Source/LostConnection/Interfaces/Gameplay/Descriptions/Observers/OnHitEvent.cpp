// Copyright (c) 2022 Use Your Imagination

#include "OnHitEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/HitEventsHolder.h"

TScriptInterface<IHitEventsHolder> IOnHitEvent::getHitEventsHolder() const
{
	return const_cast<IOnHitEvent*>(this)->getHitEventsHolder().GetObject();
}
