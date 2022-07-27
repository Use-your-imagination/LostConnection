// Copyright (c) 2022 Use Your Imagination

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

void UAilmentInflictorUtility::setDamageInstigator(const TObjectPtr<AController>& damageInstigator)
{
	damageInflictorUtility->setDamageInstigator(damageInstigator);
}

bool UAilmentInflictorUtility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInflictorUtility, *Bunch, *RepFlags);

	wroteSomething |= damageInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

float UAilmentInflictorUtility::calculateTotalDamage(const TScriptInterface<IDamageReceiver>& receiver) const
{
	return damageInflictorUtility->calculateTotalDamage(receiver);
}

FDamageStructure& UAilmentInflictorUtility::getDamage()
{
	return damageInflictorUtility->getDamage();
}

void UAilmentInflictorUtility::setDamageType_Implementation(ETypeOfDamage type)
{
	damageType = type;
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

const TObjectPtr<AController>& UAilmentInflictorUtility::getDamageInstigator() const
{
	return damageInflictorUtility->getDamageInstigator();
}
