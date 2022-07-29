// Copyright (c) 2021 Use Your Imagination

#include "CritAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"
#include "Maths/FormulaLibrary.h"

FString UCritAilment::getStatusName() const
{
	return "Crit";
}

void UCritAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCritAilment, damageMultiplierPercent);

	DOREPLIFETIME(UCritAilment, damageMultiplierPerTotalLifePercentPool);

	DOREPLIFETIME(UCritAilment, critMultiplier);
}

float UCritAilment::getCritMultiplier() const
{
	return critMultiplier;
}

void UCritAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);
}

bool UCritAilment::applyEffect(const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	if (!inflictor)
	{
		return false;
	}

	for (const TObjectPtr<UBaseStatus>& status : target->getStatuses())
	{
		if (TObjectPtr<UCritAilment> crit = Cast<UCritAilment>(status))
		{
			damageMultiplierPercent += crit->getCritMultiplier();
		}
	}

	damage->addedDamage += inflictor->calculateTotalDamage(target.GetObject()) * Utility::fromPercent(damageMultiplierPercent);

	critMultiplier = target->getTotalLifePercentDealt(inflictor.GetObject()) * damageMultiplierPerTotalLifePercentPool;

	return true;
}

ETypeOfDamage UCritAilment::getAilmentDamageType() const
{
	return ETypeOfDamage::physical;
}
