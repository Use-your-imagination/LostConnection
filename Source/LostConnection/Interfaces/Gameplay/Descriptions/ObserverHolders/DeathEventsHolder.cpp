// Copyright (c) 2021 Use Your Imagination

#include "DeathEventsHolder.h"

#include "Characters/BaseCharacter.h"

void IDeathEventsHolder::attachDeathEvent(TScriptInterface<IOnDeathEvent> event)
{
	auto& currentHolder = event->getDeathEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachDeathEvent(event.GetObject());
	}

	currentHolder = this;

	this->getDeathEvents().Add(event);
}

void IDeathEventsHolder::detachDeathEvent(TScriptInterface<IOnDeathEvent> event)
{
	this->getDeathEvents().RemoveSingle(event);
}

void IDeathEventsHolder::notifyDeathEvents(TObjectPtr<ABaseCharacter> character) const
{
	for (const auto& event : this->getDeathEvents())
	{
		event->deathEventAction(character);
	}
}

const TArray<TScriptInterface<IOnDeathEvent>>& IDeathEventsHolder::getDeathEvents() const
{
	return const_cast<IDeathEventsHolder*>(this)->getDeathEvents();
}
