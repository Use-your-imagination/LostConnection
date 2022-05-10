// Copyright (c) 2021 Use Your Imagination

#include "DeathEventsHolder.h"

void IDeathEventsHolder::notifyDeathEvents() const
{
	const TArray<TScriptInterface<IOnDeathEvent>>& events = this->getDeathEvents();

	for (const auto& event : events)
	{
		event->deathEventAction();
	}
}
