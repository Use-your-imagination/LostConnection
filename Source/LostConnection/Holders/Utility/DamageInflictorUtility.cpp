// Copyright (c) 2022 Use Your Imagination

#include "DamageInflictorUtility.h"

void UDamageInflictorUtility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDamageInflictorUtility, baseInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, addedInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, additionalInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, increaseInflictorDamageCoefficients);

	DOREPLIFETIME(UDamageInflictorUtility, moreInflictorDamageCoefficients);
}

void UDamageInflictorUtility::appendIncreaseDamageCoefficient(float coefficient)
{
	increaseInflictorDamageCoefficients.Add(coefficient);
}

void UDamageInflictorUtility::removeIncreaseDamageCoefficient(float coefficient)
{
	increaseInflictorDamageCoefficients.RemoveSingle(coefficient);
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

const TArray<float>& UDamageInflictorUtility::getIncreaseDamageCoefficients() const
{
	return increaseInflictorDamageCoefficients;
}

const TArray<float>& UDamageInflictorUtility::getMoreDamageCoefficients() const
{
	return moreInflictorDamageCoefficients;
}
