// Copyright (c) 2022 Use Your Imagination

#include "HitEventsHolder.h"

void IHitEventsHolder::notifyHitEvents() const
{
	for (const auto& event : this->getHitEvents())
	{
		event->hitEventAction();
	}
}
