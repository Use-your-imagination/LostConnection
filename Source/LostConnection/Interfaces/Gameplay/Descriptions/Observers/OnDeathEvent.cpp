// Copyright (c) 2021 Use Your Imagination

#include "OnDeathEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/DeathEventsHolder.h"

TScriptInterface<IDeathEventsHolder> IOnDeathEvent::getDeathEventsHolder() const
{
	return const_cast<IOnDeathEvent*>(this)->getDeathEventsHolder().GetObject();
}
