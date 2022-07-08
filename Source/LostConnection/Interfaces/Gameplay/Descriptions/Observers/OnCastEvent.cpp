// Copyright (c) 2022 Use Your Imagination

#include "OnCastEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/CastEventsHolder.h"

TScriptInterface<ICastEventsHolder> IOnCastEvent::getCastEventsHolder() const
{
	return const_cast<IOnCastEvent*>(this)->getCastEventsHolder().GetObject();
}
