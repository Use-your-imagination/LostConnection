// Copyright (c) 2022 Use Your Imagination

#include "BaseDamagePersonalModule.h"

#include "Interfaces/Holders/AilmentInflictorHolder.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

bool UBaseDamagePersonalModule::applyCondition(TObjectPtr<AActor> caller) const
{
	if (!Super::applyCondition(caller))
	{
		return false;
	}

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

float UBaseDamagePersonalModule::getAddedDamage() const
{
	return addedDamage;
}

float UBaseDamagePersonalModule::getIncreaseDamageCoefficient() const
{
	return increaseDamageCoefficient;
}

float UBaseDamagePersonalModule::getMoreDamageCoefficient() const
{
	return moreDamageCoefficient;
}

float UBaseDamagePersonalModule::getAdditionalDamage() const
{
	return additionalDamage;
}
