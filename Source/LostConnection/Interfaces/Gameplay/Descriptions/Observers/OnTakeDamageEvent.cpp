// Copyright (c) 2022 Use Your Imagination

#include "OnTakeDamageEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/TakeDamageEventsHolder.h"

TScriptInterface<ITakeDamageEventsHolder> IOnTakeDamageEvent::getTakeDamageEventsHolder() const
{
	return const_cast<IOnTakeDamageEvent*>(this)->getTakeDamageEventsHolder().GetObject();
}
