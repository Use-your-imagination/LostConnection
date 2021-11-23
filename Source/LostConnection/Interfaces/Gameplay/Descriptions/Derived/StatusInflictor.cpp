// Copyright (c) 2021 Use-your-imagination

#include "StatusInflictor.h"

#include "Utility/Utility.h"

void IStatusInflictor::setCrushingHitChance(float crushingHitChance)
{

}

void IStatusInflictor::setAdditionalCrushingHitChance(float additionalCrushingHitChance)
{

}

bool IStatusInflictor::getCrushingHitProc() const
{
	return Utility::checkChanceProc(this->getCrushingHitChance() + this->getAdditionalCrushingHitChance());
}
