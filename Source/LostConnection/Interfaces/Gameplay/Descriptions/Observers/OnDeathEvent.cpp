// Copyright (c) 2021 Use Your Imagination

#include "OnDeathEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/DeathEventsHolder.h"

void IOnDeathEvent::initDeathEvent(IDeathEventsHolder* holder)
{
	auto& currentHolder = this->getDeathEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachDeathEvent(this->_getUObject());
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachDeathEvent(this->_getUObject());
	}
}
