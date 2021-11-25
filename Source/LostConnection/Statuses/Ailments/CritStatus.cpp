// Copyright (c) 2021 Use-your-imagination

#include "CritStatus.h"

#include "Algo/Accumulate.h"

#include "Interfaces/Gameplay/Descriptions/Derived/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UCritStatus::getStatusName() const
{
	return "Crit";
}

SIZE_T UCritStatus::getActiveStatusesCount() const
{
	return Utility::countStatuses(target, StaticClass());
}

void UCritStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCritStatus, damageMultiplierPercent);

	DOREPLIFETIME(UCritStatus, damageMultiplierPerTotalLifePercentPool);

	DOREPLIFETIME(UCritStatus, critMultiplier);

	DOREPLIFETIME(UCritStatus, additionalDamage);
}

float UCritStatus::getCritMultiplier() const
{
	return critMultiplier;
}

bool UCritStatus::applyEffect(IAilmentReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	target->takeDamage(this);

	critMultiplier = target->getTotalLifePercentDealt(this) * damageMultiplierPerTotalLifePercentPool;

	return true;
}

void UCritStatus::setInflictorDamage_Implementation(float newDamage)
{
	inflictorDamage = newDamage;
}

void UCritStatus::setAdditionalInflictorDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
}

float UCritStatus::getInflictorDamage() const
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	float resultMultiplier = Algo::Accumulate(statuses, damageMultiplierPercent, [](float currentValue, const UBaseStatus* status)
		{
			const UCritStatus* crit = Cast<UCritStatus>(status);

			if (crit)
			{
				return currentValue + crit->getCritMultiplier();
			}

			return currentValue;
		});

	return inflictorDamage * (resultMultiplier / 100.0f);
}

float UCritStatus::getAdditionalInflictorDamage() const
{
	return additionalDamage;
}
