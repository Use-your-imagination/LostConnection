// Copyright (c) 2021 Use Your Imagination

#include "DeathEventsHolder.h"

void IDeathEventsHolder::notifyDeathEvents() const
{
	for (const auto& event : this->getDeathEvents())
	{
		event->deathEventAction();
	}
}
