// Copyright (c) 2021 Use Your Imagination

#include "DamageReceiver.h"

#include "Interfaces/Holders/DamageInflictorHolder.h"

void IDamageReceiver::takeDamageFromInflictorHolder(const TScriptInterface<IDamageInflictorHolder>& inflictorHolder)
{
	this->takeDamageFromInflictor(inflictorHolder->getDamageInflictorUtility());
}

float IDamageReceiver::getTotalLifePercentDealt(IDamageInflictorHolder* inflictor) const
{
	return this->getTotalLifePercentDealt(inflictor->getDamageInflictorUtility());
}

float IDamageReceiver::getLifePercentDealt(IDamageInflictorHolder* inflictor) const
{
	return this->getLifePercentDealt(inflictor->getDamageInflictorUtility());
}

float IDamageReceiver::getEnergyShieldPercentDealt(IDamageInflictorHolder* inflictor) const
{
	return this->getEnergyShieldPercentDealt(inflictor->getDamageInflictorUtility());
}
