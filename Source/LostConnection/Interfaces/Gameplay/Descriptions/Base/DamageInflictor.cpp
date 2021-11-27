// Copyright (c) 2021 Use-your-imagination

#include "DamageInflictor.h"

void IDamageInflictor::increaseAdditionalInflictorDamage(float amount)
{
	this->setAdditionalInflictorDamage(this->getAdditionalInflictorDamage() + amount);
}

void IDamageInflictor::decreaseAdditionalInflictorDamage(float amount)
{
	this->setAdditionalInflictorDamage(this->getAdditionalInflictorDamage() - amount);
}
