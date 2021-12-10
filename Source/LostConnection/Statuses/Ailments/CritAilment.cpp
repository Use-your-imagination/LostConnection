// Copyright (c) 2021 Use-your-imagination

#include "CritAilment.h"

#include "Algo/Accumulate.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UCritAilment::getStatusName() const
{
	return "Crit";
}

SIZE_T UCritAilment::getActiveStatusesCount() const
{
	return Utility::countStatuses(target, StaticClass());
}

void UCritAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCritAilment, damageMultiplierPercent);

	DOREPLIFETIME(UCritAilment, damageMultiplierPerTotalLifePercentPool);

	DOREPLIFETIME(UCritAilment, critMultiplier);

	DOREPLIFETIME(UCritAilment, additionalDamage);
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

bool UCritAilment::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	target->takeDamage(this);

	critMultiplier = target->getTotalLifePercentDealt(this) * damageMultiplierPerTotalLifePercentPool;

	return true;
}

void UCritAilment::setBaseDamage_Implementation(float newDamage)
{
	inflictorDamage = newDamage;
}

void UCritAilment::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
}

float UCritAilment::getBaseDamage() const
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	float resultMultiplier = Algo::Accumulate(statuses, damageMultiplierPercent, [](float currentValue, const UBaseStatus* status)
		{
			const UCritAilment* crit = Cast<UCritAilment>(status);

			if (crit)
			{
				return currentValue + crit->getCritMultiplier();
			}

			return currentValue;
		});

	return inflictorDamage * (resultMultiplier / 100.0f);
}

float UCritAilment::getAdditionalDamage() const
{
	return additionalDamage;
}

typeOfDamage UCritAilment::getAilmentDamageType() const
{
	return typeOfDamage::physical;
}
