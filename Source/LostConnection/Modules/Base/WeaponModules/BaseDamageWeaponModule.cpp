// Copyright (c) 2022 Use Your Imagination

#include "BaseDamageWeaponModule.h"

#include "Interfaces/Holders/AilmentInflictorHolder.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

bool UBaseDamageWeaponModule::applyCondition(TObjectPtr<AActor> caller) const
{
	if (IAilmentInflictorHolder* holder = Cast<IAilmentInflictorHolder>(caller))
	{
		return this->getDamageType() == holder->getAilmentInflictorUtility()->getDamageType();
	}
	else if (IAilmentInflictor* inflictor = Cast<IAilmentInflictor>(caller))
	{
		return this->getDamageType() == inflictor->getDamageType();
	}

	return false;
}

float UBaseDamageWeaponModule::getAddedDamage() const
{
	return addedDamage * this->getMultiplier();
}

float UBaseDamageWeaponModule::getIncreaseDamageCoefficient() const
{
	return increaseDamageCoefficient * this->getMultiplier();
}

float UBaseDamageWeaponModule::getMoreDamageCoefficient() const
{
	return moreDamageCoefficient * this->getMultiplier();
}

float UBaseDamageWeaponModule::getAdditionalDamage() const
{
	return additionalDamage * this->getMultiplier();
}
