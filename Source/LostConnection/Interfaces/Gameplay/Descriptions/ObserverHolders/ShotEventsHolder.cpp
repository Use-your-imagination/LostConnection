// Copyright (c) 2022 Use Your Imagination

#include "ShotEventsHolder.h"

#include "Characters/BaseCharacter.h"

void IShotEventsHolder::attachShotEvent(TScriptInterface<IOnShotEvent> event)
{
	auto& currentHolder = event->getShotEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachShotEvent(event.GetObject());
	}

	currentHolder = this;

	this->getShotEvents().Add(event);
}

void IShotEventsHolder::detachShotEvent(TScriptInterface<IOnShotEvent> event)
{
	this->getShotEvents().RemoveSingle(event);
}

void IShotEventsHolder::notifyShotEvents(TScriptInterface<IDamageInflictor> inflictor) const
{
	for (const auto& event : this->getShotEvents())
	{
		event->shotEventAction(inflictor);
	}
}

const TArray<TScriptInterface<IOnShotEvent>>& IShotEventsHolder::getShotEvents() const
{
	return const_cast<IShotEventsHolder*>(this)->getShotEvents();
}
