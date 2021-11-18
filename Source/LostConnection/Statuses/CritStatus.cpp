#include "CritStatus.h"

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

	DOREPLIFETIME(UCritStatus, multiplierPerStatus);
}

bool UCritStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	float resultMultiplier = damageMultiplier;
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	for (const auto& status : statuses)
	{
		if (Cast<UCritStatus>(status))
		{
			resultMultiplier += multiplierPerStatus;
		}
	}

	target->takeStatusDamage(inflictorDamage * resultMultiplier);

	return true;
}
