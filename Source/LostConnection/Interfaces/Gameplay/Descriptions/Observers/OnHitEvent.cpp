// Copyright (c) 2022 Use Your Imagination

#include "OnHitEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/HitEventsHolder.h"

void IOnHitEvent::initHitEvent(IHitEventsHolder* holder)
{
	auto& currentHolder = this->getHitEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachHitEvent(this->_getUObject());
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachHitEvent(this->_getUObject());
	}
}
