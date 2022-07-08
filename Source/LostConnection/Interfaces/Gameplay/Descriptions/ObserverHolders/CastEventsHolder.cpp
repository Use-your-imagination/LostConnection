// Copyright (c) 2022 Use Your Imagination

#include "CastEventsHolder.h"

#include "Interfaces/Gameplay/Descriptions/Caster.h"

void ICastEventsHolder::attachCastEvent(TScriptInterface<IOnCastEvent> event)
{
	auto& currentHolder = event->getCastEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachCastEvent(event.GetObject());
	}

	currentHolder = this;

	this->getCastEvents().Add(event);
}

void ICastEventsHolder::detachCastEvent(TScriptInterface<IOnCastEvent> event)
{
	this->getCastEvents().RemoveSingle(event);
}

void ICastEventsHolder::notifyCastEvents(TScriptInterface<ICaster> caster) const
{
	for (const auto& event : this->getCastEvents())
	{
		event->castEventAction(caster);
	}
}

const TArray<TScriptInterface<IOnCastEvent>>& ICastEventsHolder::getCastEvents() const
{
	return const_cast<ICastEventsHolder*>(this)->getCastEvents();
}
