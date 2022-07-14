// Copyright (c) 2021 Use Your Imagination

#include "DamageInflictor.h"

#include "Interfaces/Gameplay/Descriptions/DamageAffecter.h"

FDamageStructure::FDamageStructure(const FDamageStructure& base, const TArray<TObjectPtr<UNetworkObject>>& affecters) :
	FDamageStructure(base)
{
	for (const TObjectPtr<UNetworkObject>& affecter : affecters)
	{
		Cast<IDamageAffecter>(affecter)->affect(*this);
	}
}

FDamageStructure::FDamageStructure(const FDamageStructure& other)
{
	(*this) = other;
}

FDamageStructure& FDamageStructure::operator = (const FDamageStructure& other)
{
	baseDamage = other.baseDamage;
	addedDamage = other.addedDamage;
	additionalDamage = other.additionalDamage;
	increaseDamageCoefficients = other.increaseDamageCoefficients;
	moreDamageCoefficients = other.moreDamageCoefficients;

	return *this;
}

const FDamageStructure& IDamageInflictor::getDamage() const
{
	return const_cast<IDamageInflictor*>(this)->getDamage();
}
