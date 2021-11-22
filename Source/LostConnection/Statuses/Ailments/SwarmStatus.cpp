// Copyright (c) 2021 Use-your-imagination

#include "SwarmStatus.h"

#include "Interfaces/Gameplay/Descriptions/Derived/StatusReceiver.h"

#pragma warning(disable: 4458)

FString USwarmStatus::getStatusName() const
{
	return "Swarm";
}

void USwarmStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USwarmStatus, baseThreshold);

	DOREPLIFETIME(USwarmStatus, thresholdPerTotalLifePercentPool);
	
	DOREPLIFETIME(USwarmStatus, percentsPerSatellite);

	DOREPLIFETIME(USwarmStatus, threshold);
}

void USwarmStatus::increaseThreshold(float inflictorDamage)
{
	threshold += target->getTotalLifePercentDealt(inflictorDamage) * thresholdPerTotalLifePercentPool;
}

float USwarmStatus::getThreshold() const
{
	return threshold;
}

void USwarmStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	for (const auto& status : statuses)
	{
		USwarmStatus* swarm = Cast<USwarmStatus>(status);

		if (swarm)
		{
			swarm->increaseThreshold(inflictorDamage);
			
			swarm->refreshDuration();

			target->setUnderStatusIntVariable(this->getStatusCountKey(), FMath::Max<int32>(1, static_cast<int32>(this->getThreshold() / percentsPerSatellite)));

			return;
		}
	}

	Super::applyStatus_Implementation(inflictor, target, hit);

	target->applySwarmStatus(this);

	target->setUnderStatusIntVariable("StatusCount", 1);
}
