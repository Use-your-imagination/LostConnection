// Copyright (c) 2021 Use-your-imagination

#include "DamageInflictor.h"

void IDamageInflictor::increaseBaseDamage(float amount)
{
	this->setBaseDamage(this->getBaseDamage() + amount);
}

void IDamageInflictor::decreaseBaseDamage(float amount)
{
	this->setBaseDamage(this->getBaseDamage() - amount);
}

void IDamageInflictor::increaseAdditionalDamage(float amount)
{
	this->setAdditionalDamage(this->getAdditionalDamage() + amount);
}

void IDamageInflictor::decreaseAdditionalDamage(float amount)
{
	this->setAdditionalDamage(this->getAdditionalDamage() - amount);
}

float IDamageInflictor::getTotalDamage() const
{

}
