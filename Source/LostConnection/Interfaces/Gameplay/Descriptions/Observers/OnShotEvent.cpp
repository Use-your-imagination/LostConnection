// Copyright (c) 2022 Use Your Imagination

#include "OnShotEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/ShotEventsHolder.h"

void IOnShotEvent::initShotEvent(class IShotEventsHolder* holder)
{
	auto& currentHolder = this->getShotEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachShotEvent(this->_getUObject());
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachShotEvent(this->_getUObject());
	}
}
