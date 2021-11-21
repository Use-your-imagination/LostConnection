#include "CritStatus.h"

#include "Algo/Accumulate.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
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

	DOREPLIFETIME(UCritStatus, damageMultiplier);

	DOREPLIFETIME(UCritStatus, damageMultiplierPerTotalLifePool);
}

float UCritStatus::getMultiplier() const
{
	return multiplier;
}

bool UCritStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	float resultMultiplier = Algo::Accumulate(statuses, damageMultiplier, [](float currentValue, const UBaseStatus* status)
		{
			const UCritStatus* crit = Cast<UCritStatus>(status);

			if (crit)
			{
				return currentValue + crit->getMultiplier();
			}

			return currentValue;
		});

	target->takeStatusDamage(inflictorDamage * resultMultiplier);

	multiplier = target->getTotalLifePercentDealt(inflictorDamage) * damageMultiplierPerTotalLifePool;

	return true;
}
