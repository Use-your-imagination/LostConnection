// Copyright (c) 2022 Use-your-imagination

#include "AilmentInflictorUtility.h"

void UAilmentInflictorUtility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAilmentInflictorUtility, baseCrushingHitChance);
	
	DOREPLIFETIME(UAilmentInflictorUtility, additionalCrushingHitChance);
	
	DOREPLIFETIME(UAilmentInflictorUtility, damageType);

	DOREPLIFETIME(UAilmentInflictorUtility, damageInflictorUtility);
}

UAilmentInflictorUtility::UAilmentInflictorUtility()
{
	damageInflictorUtility = CreateDefaultSubobject<UDamageInflictorUtility>("DamageInflictorUtility");
}

bool UAilmentInflictorUtility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInflictorUtility, *Bunch, *RepFlags);

	damageInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

void UAilmentInflictorUtility::appendIncreasedDamageCoefficient(float coefficient)
{
	damageInflictorUtility->appendIncreasedDamageCoefficient(coefficient);
}

void UAilmentInflictorUtility::removeIncreasedDamageCoefficient(float coefficient)
{
	damageInflictorUtility->removeIncreasedDamageCoefficient(coefficient);
}

void UAilmentInflictorUtility::appendMoreDamageCoefficient(float coefficient)
{
	damageInflictorUtility->appendMoreDamageCoefficient(coefficient);
}

void UAilmentInflictorUtility::removeMoreDamageCoefficient(float coefficient)
{
	damageInflictorUtility->removeMoreDamageCoefficient(coefficient);
}

void UAilmentInflictorUtility::setBaseDamage_Implementation(float newDamage)
{
	damageInflictorUtility->setBaseDamage_Implementation(newDamage);
}

void UAilmentInflictorUtility::setAddedDamage_Implementation(float newAddedDamage)
{
	damageInflictorUtility->setAddedDamage_Implementation(newAddedDamage);
}

void UAilmentInflictorUtility::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	damageInflictorUtility->setAdditionalDamage_Implementation(newAdditionalDamage);
}

float UAilmentInflictorUtility::getBaseDamage() const
{
	return damageInflictorUtility->getBaseDamage();
}

float UAilmentInflictorUtility::getAddedDamage() const
{
	return damageInflictorUtility->getAddedDamage();
}

float UAilmentInflictorUtility::getAdditionalDamage() const
{
	return damageInflictorUtility->getAdditionalDamage();
}

const TArray<float>& UAilmentInflictorUtility::getIncreasedDamageCoefficients() const
{
	return damageInflictorUtility->getIncreasedDamageCoefficients();
}

const TArray<float>& UAilmentInflictorUtility::getMoreDamageCoefficients() const
{
	return damageInflictorUtility->getMoreDamageCoefficients();
}

void UAilmentInflictorUtility::setBaseCrushingHitChance_Implementation(float crushingHitChance)
{
	baseCrushingHitChance = crushingHitChance;
}

void UAilmentInflictorUtility::setAdditionalCrushingHitChance_Implementation(float newAdditionalCrushingHitChance)
{
	additionalCrushingHitChance = newAdditionalCrushingHitChance;
}

ETypeOfDamage UAilmentInflictorUtility::getDamageType() const
{
	return damageType;
}

float UAilmentInflictorUtility::getBaseCrushingHitChance() const
{
	return baseCrushingHitChance;
}

float UAilmentInflictorUtility::getAdditionalCrushingHitChance() const
{
	return additionalCrushingHitChance;
}