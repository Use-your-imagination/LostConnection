// Copyright (c) 2021 Use-your-imagination

#include "DeathEventsHolder.h"

void IDeathEventsHolder::notifyDeathEvents() const
{
	const TArray<IOnDeathEvent*>& events = this->getDeathEvents();

	for (const auto& event : events)
	{
		event->deathEventAction();
	}
}
