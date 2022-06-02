// Copyright (c) 2021 Use Your Imagination

#include "DamageInflictor.h"

#include "Maths/FormulaLibrary.h"

float IDamageInflictor::calculateTotalDamage() const
{
	return UFormulaLibrary::standardFormula
	(
		this->getBaseDamage(),
		this->getAddedDamage(),
		this->getIncreaseDamageCoefficients(),
		this->getMoreDamageCoefficients(),
		this->getAdditionalDamage()
	);
}
