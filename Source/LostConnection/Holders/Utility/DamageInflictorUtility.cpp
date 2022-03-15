// Copyright (c) 2022 Use-your-imagination

#include "DamageInflictorUtility.h"

void UDamageInflictorUtility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDamageInflictorUtility, baseInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, addedInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, additionalInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, increasedInflictorDamageCoefficients);

	DOREPLIFETIME(UDamageInflictorUtility, moreInflictorDamageCoefficients);
}

void UDamageInflictorUtility::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedInflictorDamageCoefficients.Add(coefficient);
}

void UDamageInflictorUtility::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedInflictorDamageCoefficients.RemoveSingle(coefficient);
}

void UDamageInflictorUtility::appendMoreDamageCoefficient(float coefficient)
{
	moreInflictorDamageCoefficients.Add(coefficient);
}

void UDamageInflictorUtility::removeMoreDamageCoefficient(float coefficient)
{
	moreInflictorDamageCoefficients.RemoveSingle(coefficient);
}

void UDamageInflictorUtility::setBaseDamage_Implementation(float newDamage)
{
	baseInflictorDamage = newDamage;
}

void UDamageInflictorUtility::setAddedDamage_Implementation(float newAddedDamage)
{
	addedInflictorDamage = newAddedDamage;
}

void UDamageInflictorUtility::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	additionalInflictorDamage = newAdditionalDamage;
}

float UDamageInflictorUtility::getBaseDamage() const
{
	return baseInflictorDamage;
}

float UDamageInflictorUtility::getAddedDamage() const
{
	return addedInflictorDamage;
}

float UDamageInflictorUtility::getAdditionalDamage() const
{
	return additionalInflictorDamage;
}

TArray<float> UDamageInflictorUtility::getIncreasedDamageCoefficients() const
{
	return increasedInflictorDamageCoefficients;
}

TArray<float> UDamageInflictorUtility::getMoreDamageCoefficients() const
{
	return moreInflictorDamageCoefficients;
}
