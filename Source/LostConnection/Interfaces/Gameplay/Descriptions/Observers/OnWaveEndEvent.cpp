// Copyright (c) 2022 Use Your Imagination

#include "OnWaveEndEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/WaveEndEventsHolder.h"

void IOnWaveEndEvent::initWaveEndEvent(class IWaveEndEventsHolder* holder)
{
	auto& currentHolder = this->getWaveEndEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachWaveEndEvent(this->_getUObject());
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachWaveEndEvent(this->_getUObject());
	}
}
