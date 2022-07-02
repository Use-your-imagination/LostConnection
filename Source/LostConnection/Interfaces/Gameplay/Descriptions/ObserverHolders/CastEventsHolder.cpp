// Copyright (c) 2022 Use Your Imagination

#include "CastEventsHolder.h"

void ICastEventsHolder::attachCastEvent(const TScriptInterface<IOnCastEvent>& event)
{
	auto& currentHolder = event->getCastEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachCastEvent(event.GetObject());
	}

	currentHolder = this;

	this->getCastEvents().Add(event);
}

void ICastEventsHolder::detachCastEvent(const TScriptInterface<IOnCastEvent>& event)
{
	this->getCastEvents().RemoveSingle(event);
}

void ICastEventsHolder::notifyCastEvents() const
{
	for (const auto& event : this->getCastEvents())
	{
		event->castEventAction();
	}
}

const TArray<TScriptInterface<IOnCastEvent>>& ICastEventsHolder::getCastEvents() const
{
	return const_cast<ICastEventsHolder*>(this)->getCastEvents();
}
