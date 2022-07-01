// Copyright (c) 2022 Use Your Imagination

#include "OnWaveBeginEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/WaveBeginEventsHolder.h"

void IOnWaveBeginEvent::initWaveBeginEvent(class IWaveBeginEventsHolder* holder)
{
	auto& currentHolder = this->getWaveBeginEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachWaveBeginEvent(this->_getUObject());
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachWaveBeginEvent(this->_getUObject());
	}
}
