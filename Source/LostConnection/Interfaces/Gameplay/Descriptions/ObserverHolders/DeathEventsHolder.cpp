// Copyright (c) 2021 Use Your Imagination

#include "DeathEventsHolder.h"

void IDeathEventsHolder::attachDeathEvent(const TScriptInterface<IOnDeathEvent>& event)
{
	auto& currentHolder = event->getDeathEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachDeathEvent(event.GetObject());
	}

	currentHolder = this;

	this->getDeathEvents().Add(event);
}

void IDeathEventsHolder::detachDeathEvent(const TScriptInterface<IOnDeathEvent>& event)
{
	this->getDeathEvents().RemoveSingle(event);
}

void IDeathEventsHolder::notifyDeathEvents() const
{
	for (const auto& event : this->getDeathEvents())
	{
		event->deathEventAction();
	}
}

const TArray<TScriptInterface<IOnDeathEvent>>& IDeathEventsHolder::getDeathEvents() const
{
	return const_cast<IDeathEventsHolder*>(this)->getDeathEvents();
}
