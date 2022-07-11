// Copyright (c) 2022 Use Your Imagination

#include "DamageInflictorUtility.h"

#include "Utility/Utility.h"

void UDamageInflictorUtility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDamageInflictorUtility, baseInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, addedInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, additionalInflictorDamage);

	DOREPLIFETIME(UDamageInflictorUtility, increaseInflictorDamageCoefficients);

	DOREPLIFETIME(UDamageInflictorUtility, moreInflictorDamageCoefficients);

	DOREPLIFETIME(UDamageInflictorUtility, damageInstigator);
}

void UDamageInflictorUtility::setDamageInstigator_Implementation(AController* newDamageInstigator)
{
	damageInstigator = newDamageInstigator;
}

void UDamageInflictorUtility::PostInitProperties()
{
	Super::PostInitProperties();

	if (TObjectPtr<APawn> pawn = Cast<APawn>(GetOutermostObject()))
	{
		TObjectPtr<AController> controller = pawn->GetController();

		if (controller && controller->HasAuthority())
		{
			damageInstigator = controller;
		}
	}
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

TObjectPtr<AController> UDamageInflictorUtility::getDamageInstigator() const
{
	return damageInstigator;
}

bool UDamageInflictorUtility::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInstigator, *Bunch, *RepFlags);

	return wroteSomething;
}
