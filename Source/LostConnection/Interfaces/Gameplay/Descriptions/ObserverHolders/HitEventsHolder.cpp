// Copyright (c) 2022 Use Your Imagination

#include "HitEventsHolder.h"

void IHitEventsHolder::attachHitEvent(const TScriptInterface<IOnHitEvent>& event)
{
	auto& currentHolder = event->getHitEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachHitEvent(event.GetObject());
	}

	currentHolder = this;

	this->getHitEvents().Add(event);
}

void IHitEventsHolder::detachHitEvent(const TScriptInterface<IOnHitEvent>& event)
{
	this->getHitEvents().RemoveSingle(event);
}

void IHitEventsHolder::notifyHitEvents() const
{
	for (const auto& event : this->getHitEvents())
	{
		event->hitEventAction();
	}
}

const TArray<TScriptInterface<IOnHitEvent>>& IHitEventsHolder::getHitEvents() const
{
	return const_cast<IHitEventsHolder*>(this)->getHitEvents();
}
