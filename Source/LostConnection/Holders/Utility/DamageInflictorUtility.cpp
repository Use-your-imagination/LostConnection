// Copyright (c) 2022 Use Your Imagination

#include "DamageInflictorUtility.h"

#include "Utility/Utility.h"
#include "Maths/FormulaLibrary.h"

void UDamageInflictorUtility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDamageInflictorUtility, damage);
}

void UDamageInflictorUtility::setDamageInstigator_Implementation(AController* newDamageInstigator)
{
	damageInstigator = newDamageInstigator;
}

float UDamageInflictorUtility::calculateTotalDamage(const TScriptInterface<IDamageReceiver>& receiver) const
{
	TArray<TScriptInterface<IDamageAffecter>> affecters;

	if (TObjectPtr<ALostConnectionPlayerState> playerState = damageInstigator->GetPlayerState<ALostConnectionPlayerState>())
	{
		affecters = playerState->getDamageAffecters();
	}

	FDamageStructure totalDamage(damage, affecters, const_cast<UDamageInflictorUtility*>(this), receiver);

	return UFormulaLibrary::standardFormulaDamage(totalDamage);
}

FDamageStructure& UDamageInflictorUtility::getDamage()
{
	return damage;
}

const TObjectPtr<AController>& UDamageInflictorUtility::getDamageInstigator() const
{
	return damageInstigator;
}
