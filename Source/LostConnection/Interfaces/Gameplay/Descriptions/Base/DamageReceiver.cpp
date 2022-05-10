// Copyright (c) 2021 Use Your Imagination

#include "DamageReceiver.h"

#include "Interfaces/Holders/DamageInflictorHolder.h"

void IDamageReceiver::takeDamageFromInflictorHolder(const IDamageInflictorHolder* inflictorHolder)
{
	this->takeDamageFromInflictor(TScriptInterface<IDamageInflictor>(inflictorHolder->getDamageInflictorUtility()));
}

float IDamageReceiver::getTotalLifePercentDealt(IDamageInflictorHolder* inflictorHolder) const
{
	return this->getTotalLifePercentDealt(inflictorHolder->getDamageInflictorUtility());
}

float IDamageReceiver::getLifePercentDealt(IDamageInflictorHolder* inflictorHolder) const
{
	return this->getLifePercentDealt(inflictorHolder->getDamageInflictorUtility());
}

float IDamageReceiver::getEnergyShieldPercentDealt(IDamageInflictorHolder* inflictorHolder) const
{
	return this->getEnergyShieldPercentDealt(inflictorHolder->getDamageInflictorUtility());
}
