// Copyright (c) 2022 Use Your Imagination

#include "TakeDamageEventsHolder.h"

void ITakeDamageEventsHolder::notifyTakeDamageEvents() const
{
	for (const auto& event : this->getTakeDamageEvents())
	{
		event->takeDamageEventAction();
	}
}
