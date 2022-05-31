// Copyright (c) 2021 Use Your Imagination

#include "DamageModule.h"

#include "Interfaces/Holders/AilmentInflictorHolder.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

bool IDamageModule::applyCondition(TObjectPtr<AActor> caller) const
{
	if (caller->Implements<UAilmentInflictorHolder>())
	{
		return this->getDamageType() == Cast<IAilmentInflictorHolder>(caller)->getAilmentInflictorUtility()->getDamageType();
	}
	else if (caller->Implements<UAilmentInflictor>())
	{
		return this->getDamageType() == Cast<IAilmentInflictor>(caller)->getDamageType();
	}

	return false;
}

ETypeOfDamage IDamageModule::getDamageType() const
{
	return ETypeOfDamage::any;
}
