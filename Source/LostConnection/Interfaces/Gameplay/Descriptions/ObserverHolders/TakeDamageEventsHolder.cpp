// Copyright (c) 2022 Use Your Imagination

#include "TakeDamageEventsHolder.h"

void ITakeDamageEventsHolder::attachTakeDamageEvent(const TScriptInterface<IOnTakeDamageEvent>& event)
{
	auto& currentHolder = event->getTakeDamageEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachTakeDamageEvent(event.GetObject());
	}

	currentHolder = this;

	this->getTakeDamageEvents().Add(event);
}

void ITakeDamageEventsHolder::detachTakeDamageEvent(const TScriptInterface<IOnTakeDamageEvent>& event)
{
	this->getTakeDamageEvents().RemoveSingle(event);
}

void ITakeDamageEventsHolder::notifyTakeDamageEvents() const
{
	for (const auto& event : this->getTakeDamageEvents())
	{
		event->takeDamageEventAction();
	}
}

const TArray<TScriptInterface<IOnTakeDamageEvent>>& ITakeDamageEventsHolder::getTakeDamageEvents() const
{
	return const_cast<ITakeDamageEventsHolder*>(this)->getTakeDamageEvents();
}
