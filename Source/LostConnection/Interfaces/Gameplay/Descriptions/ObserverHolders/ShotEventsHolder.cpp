// Copyright (c) 2022 Use Your Imagination

#include "ShotEventsHolder.h"

void IShotEventsHolder::attachShotEvent(const TScriptInterface<IOnShotEvent>& event)
{
	auto& currentHolder = event->getShotEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachShotEvent(event.GetObject());
	}

	currentHolder = this;

	this->getShotEvents().Add(event);
}

void IShotEventsHolder::detachShotEvent(const TScriptInterface<IOnShotEvent>& event)
{
	this->getShotEvents().RemoveSingle(event);
}

void IShotEventsHolder::notifyShotEvents() const
{
	for (const auto& event : this->getShotEvents())
	{
		event->shotEventAction();
	}
}

const TArray<TScriptInterface<IOnShotEvent>>& IShotEventsHolder::getShotEvents() const
{
	return const_cast<IShotEventsHolder*>(this)->getShotEvents();
}
