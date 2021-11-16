#include "CritStatus.h"

#include "Algo/Count.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"
#include "Characters/BaseCharacter.h"

FString UCritStatus::getStatusName() const
{
	return "Crit";
}

void UCritStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCritStatus, damageMultiplier);

	DOREPLIFETIME(UCritStatus, multiplierPerStatus);
}

void UCritStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	float resultMultiplier = damageMultiplier;
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	for (const auto& status : statuses)
	{
		if (Cast<UCritStatus>(status))
		{
			resultMultiplier += multiplierPerStatus;
		}
	}

	target->takeStatusDamage(inflictor->getInflictorDamage() * resultMultiplier);
}

void UCritStatus::postRemove()
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	target->setUnderStatusIntVariable
	(
		this->getStatusCountKey(),
		Algo::CountIf(statuses, [](const UBaseStatus* status) { return static_cast<bool>(Cast<UCritStatus>(status)); })
	);
}
