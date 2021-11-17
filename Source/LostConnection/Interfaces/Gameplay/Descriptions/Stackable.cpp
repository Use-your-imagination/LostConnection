// Copyright (c) 2021 Use-your-imagination

#include "Stackable.h"

float IStackable::calculateStacks(float damage) const
{
	return damage * this->getDamageToStacksCoefficient();
}

bool IStackable::increaseStacksCondition(float damage) const
{
	return true;
}

bool IStackable::decreaseStacksCondition(float damage) const
{
	return this->getStacks() - this->calculateStacks(damage) > 0;
}

void IStackable::increaseStacks(float damage)
{
	if (this->increaseStacksCondition(damage))
	{
		this->getStacks() += calculateStacks(damage);
	}
}

void IStackable::decreaseStacks(float damage)
{
	if (this->decreaseStacksCondition(damage))
	{
		this->getStacks() -= calculateStacks(damage);
	}
}
