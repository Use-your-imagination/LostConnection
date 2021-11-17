#include "SwarmStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

FString USwarmStatus::getStatusName() const
{
	return "Swarm";
}

bool USwarmStatus::increaseStacksCondition(float damage) const
{
	return damage * limitDamageToStacksCoefficient > stacks;
}

void USwarmStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USwarmStatus, poisonDamageCoefficient);

	DOREPLIFETIME(USwarmStatus, damageToStacksCoefficient);

	DOREPLIFETIME(USwarmStatus, limitDamageToStacksCoefficient);

	DOREPLIFETIME(USwarmStatus, stacksToThresholdCoefficient);

	DOREPLIFETIME(USwarmStatus, rampUpCoefficient);

	DOREPLIFETIME(USwarmStatus, percentsPerSatellite);

	DOREPLIFETIME(USwarmStatus, poisonDamage);

	DOREPLIFETIME(USwarmStatus, stacks);
}

float USwarmStatus::getThreshold() const
{
	return (1.0f - rampUpCoefficient / (rampUpCoefficient + stacks * stacksToThresholdCoefficient)) * 100.0f;
}

void USwarmStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	for (const auto& status : statuses)
	{
		USwarmStatus* swarm = Cast<USwarmStatus>(status);

		if (swarm)
		{
			swarm->increaseStacks(inflictor->getInflictorDamage());

			target->setUnderStatusIntVariable(this->getStatusCountKey(), FMath::Max<int32>(1, static_cast<int32>(this->getThreshold() / percentsPerSatellite)));

			return;
		}
	}

	Super::applyStatus_Implementation(inflictor, target, hit);

	poisonDamage = inflictor->getInflictorDamage() * poisonDamageCoefficient;

	target->applySwarmStatus(this);

	target->setUnderStatusIntVariable("StatusCount", 1);
}

void USwarmStatus::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	Super::applyEffect(target, hit);

	target->takeStatusDamage(poisonDamage);
}

void USwarmStatus::postRemove()
{
	target->setUnderStatusIntVariable(this->getStatusCountKey(), 0);
}

float USwarmStatus::getDamageToStacksCoefficient() const
{
	return damageToStacksCoefficient;
}

float& USwarmStatus::getStacks()
{
	return stacks;
}

float USwarmStatus::getStacks() const
{
	return stacks;
}
