// Copyright (c) 2021 Use-your-imagination

#include "AilmentInflictor.h"

#include "Utility/Utility.h"

void IAilmentInflictor::setBaseCrushingHitChance(float crushingHitChance)
{

}

void IAilmentInflictor::setAdditionalCrushingHitChance(float additionalCrushingHitChance)
{

}

bool IAilmentInflictor::getCrushingHitProc() const
{
	return Utility::checkChanceProc(this->getBaseCrushingHitChance() + this->getAdditionalCrushingHitChance());
}
