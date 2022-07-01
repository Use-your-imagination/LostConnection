// Copyright (c) 2022 Use Your Imagination

#include "CastEventsHolder.h"

void ICastEventsHolder::notifyCastEvents() const
{
	for (const auto& event : this->getCastEvents())
	{
		event->castEventAction();
	}
}
