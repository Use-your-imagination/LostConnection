// Copyright (c) 2021 Use Your Imagination

#include "DamageReceiver.h"

#include "Interfaces/Holders/DamageInflictorHolder.h"

void IDamageReceiver::takeDamageFromInflictorHolder(const TScriptInterface<IDamageInflictorHolder>& inflictorHolder)
{
	this->takeDamageFromInflictor(inflictorHolder->getDamageInflictorUtility());
}
