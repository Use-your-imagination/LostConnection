// Copyright (c) 2022 Use Your Imagination

#include "OnTakeDamageEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/TakeDamageEventsHolder.h"

void IOnTakeDamageEvent::initTakeDamageEvent(class ITakeDamageEventsHolder* holder)
{
	auto& currentHolder = this->getTakeDamageEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachTakeDamageEvent(this->_getUObject());
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachTakeDamageEvent(this->_getUObject());
	}
}
