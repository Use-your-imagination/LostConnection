// Copyright (c) 2022 Use Your Imagination

#include "DamageInflictorUtility.h"

#include "Utility/Utility.h"
#include "Maths/FormulaLibrary.h"

void UDamageInflictorUtility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDamageInflictorUtility, damage);

	DOREPLIFETIME(UDamageInflictorUtility, damageAffecters);
}

void UDamageInflictorUtility::setDamageInstigator_Implementation(AController* newDamageInstigator)
{
	damageInstigator = newDamageInstigator;
}

bool UDamageInflictorUtility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (const auto& damageAffecter : damageAffecters)
	{
		wroteSomething |= Channel->ReplicateSubobject(damageAffecter, *Bunch, *RepFlags);

		wroteSomething |= damageAffecter->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return wroteSomething;
}

float UDamageInflictorUtility::calculateTotalDamage() const
{
	FDamageStructure totalDamage(damage, damageAffecters);

	return UFormulaLibrary::standardFormula
	(
		totalDamage.baseDamage,
		totalDamage.addedDamage,
		totalDamage.increaseDamageCoefficients,
		totalDamage.moreDamageCoefficients,
		totalDamage.additionalDamage
	);
}

FDamageStructure& UDamageInflictorUtility::getDamage()
{
	return damage;
}

const TObjectPtr<AController>& UDamageInflictorUtility::getDamageInstigator() const
{
	return damageInstigator;
}
