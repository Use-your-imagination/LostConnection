// Copyright (c) 2022 Use Your Imagination

#include "OnShotEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/ShotEventsHolder.h"

TScriptInterface<IShotEventsHolder> IOnShotEvent::getShotEventsHolder() const
{
	return const_cast<IOnShotEvent*>(this)->getShotEventsHolder().GetObject();
}
