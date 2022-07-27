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
	TArray<TScriptInterface<IDamageAffecter>> inflictorAffecters;
	TArray<TScriptInterface<IDamageAffecter>> receiverAffecters;
	TScriptInterface<IDamageInflictor> infictor = const_cast<UDamageInflictorUtility*>(this);

	if (TObjectPtr<ALostConnectionPlayerState> playerState = damageInstigator->GetPlayerState<ALostConnectionPlayerState>())
	{
		inflictorAffecters = playerState->getAttackAffecters();
	}

	if (TObjectPtr<ALostConnectionPlayerState> playerState = Utility::getPlayerState(Cast<APawn>(receiver)))
	{
		receiverAffecters = playerState->getDefenceAffecters();
	}

	return UFormulaLibrary::standardFormulaDamage
	(
		FDamageStructure
		(
			UFormulaLibrary::standardFormulaDamage(FDamageStructure(damage, inflictorAffecters, infictor, receiver)), // damage before resists
			receiverAffecters,
			infictor,
			receiver
		)
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
