// Copyright (c) 2022 Use Your Imagination

#include "OnCastEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/CastEventsHolder.h"

void IOnCastEvent::initCastEvent(class ICastEventsHolder* holder)
{
	auto& currentHolder = this->getCastEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachCastEvent(this->_getUObject());
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachCastEvent(this->_getUObject());
	}
}
