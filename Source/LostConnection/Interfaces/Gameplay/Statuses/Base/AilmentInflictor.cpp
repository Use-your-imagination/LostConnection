// Copyright (c) 2021 Use Your Imagination

#include "AilmentInflictor.h"

#include "Utility/Utility.h"

void IAilmentInflictor::setBaseCrushingHitChance(float crushingHitChance)
{

}

void IAilmentInflictor::setAdditionalCrushingHitChance(float additionalCrushingHitChance)
{

}

void IAilmentInflictor::setDamageType(ETypeOfDamage type)
{

}

bool IAilmentInflictor::getCrushingHitProc() const
{
	return Utility::checkChanceProc(this->getBaseCrushingHitChance() + this->getAdditionalCrushingHitChance());
}
