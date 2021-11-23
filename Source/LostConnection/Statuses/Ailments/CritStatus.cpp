// Copyright (c) 2021 Use-your-imagination

#include "CritStatus.h"

#include "Algo/Accumulate.h"

#include "Interfaces/Gameplay/Descriptions/Derived/StatusReceiver.h"
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
}

float UCritStatus::getCritMultiplier() const
{
	return critMultiplier;
}

bool UCritStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	target->takeDamage(this);

	critMultiplier = target->getTotalLifePercentDealt(inflictorDamage) * damageMultiplierPerTotalLifePercentPool;

	return true;
}

float UCritStatus::getInflictorDamage() const
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	float resultMultiplier = Algo::Accumulate(statuses, damageMultiplierPercent, [](float currentValue, const UBaseStatus* status)
		{
			const UCritStatus* crit = Cast<UCritStatus>(status);

			if (crit)
			{
				return currentValue + crit->getMultiplier();
			}

			return currentValue;
		});

	return inflictorDamage * (resultMultiplier / 100.0f);
}