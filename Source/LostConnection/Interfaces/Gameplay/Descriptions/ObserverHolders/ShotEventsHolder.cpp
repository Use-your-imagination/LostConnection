// Copyright (c) 2022 Use Your Imagination

#include "ShotEventsHolder.h"

void IShotEventsHolder::notifyShotEvents() const
{
	const auto& events = this->getShotEvents();

	for (const auto& event : events)
	{
		event->shotEventAction();
	}
}
