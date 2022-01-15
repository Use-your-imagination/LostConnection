// Copyright (c) 2021 Use-your-imagination

#include "OnDeathEvent.h"

#include "Interfaces/Gameplay/Descriptions/ObserverHolders/GameplayEvents/DeathEventsHolder.h"

void IOnDeathEvent::initDeathEvent(IDeathEventsHolder* holder)
{
	TWeakInterfacePtr<IDeathEventsHolder>& currentHolder = this->getDeathEventsHolder();

	if (currentHolder.IsValid())
	{
		currentHolder->detachDeathEvent(this);
	}

	currentHolder = holder;

	if (currentHolder.IsValid())
	{
		currentHolder->attachDeathEvent(this);
	}	
}
