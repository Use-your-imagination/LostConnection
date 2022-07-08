// Copyright (c) 2022 Use Your Imagination

#include "HitEventsHolder.h"

#include "Characters/BaseCharacter.h"

void IHitEventsHolder::attachHitEvent(TScriptInterface<IOnHitEvent> event)
{
	auto& currentHolder = event->getHitEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachHitEvent(event.GetObject());
	}

	currentHolder = this;

	this->getHitEvents().Add(event);
}

void IHitEventsHolder::detachHitEvent(TScriptInterface<IOnHitEvent> event)
{
	this->getHitEvents().RemoveSingle(event);
}

void IHitEventsHolder::notifyHitEvents(TWeakObjectPtr<ABaseCharacter> hitter, TObjectPtr<ABaseCharacter> target) const
{
	for (const auto& event : this->getHitEvents())
	{
		event->hitEventAction(hitter, target);
	}
}

const TArray<TScriptInterface<IOnHitEvent>>& IHitEventsHolder::getHitEvents() const
{
	return const_cast<IHitEventsHolder*>(this)->getHitEvents();
}
