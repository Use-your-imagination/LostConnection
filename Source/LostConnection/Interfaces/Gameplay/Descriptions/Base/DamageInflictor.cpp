// Copyright (c) 2021 Use Your Imagination

#include "DamageInflictor.h"

#include "Interfaces/Gameplay/Descriptions/DamageAffecter.h"

FDamageStructure::FDamageStructure() :
	baseDamage(0.0f),
	addedDamage(0.0f),
	additionalDamage(0.0f)
{

}

FDamageStructure::FDamageStructure(const FDamageStructure& base, const TArray<TScriptInterface<IDamageAffecter>>& affecters, const TScriptInterface<IDamageInflictor>& inflictor, const TScriptInterface<IDamageReceiver>& receiver) :
	FDamageStructure(base)
{
	for (const TScriptInterface<IDamageAffecter>& affecter : affecters)
	{
		if (affecter && affecter->affectCondition(inflictor, receiver))
		{
			affecter->affect(*this);
		}
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
