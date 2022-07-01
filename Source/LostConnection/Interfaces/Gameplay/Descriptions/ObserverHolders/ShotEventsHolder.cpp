// Copyright (c) 2022 Use Your Imagination

#include "ShotEventsHolder.h"

void IShotEventsHolder::notifyShotEvents() const
{
	for (const auto& event : this->getShotEvents())
	{
		event->shotEventAction();
	}
}
