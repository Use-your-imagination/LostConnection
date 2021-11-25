// Copyright (c) 2021 Use-your-imagination

#include "SwarmStatus.h"

#include "Interfaces/Gameplay/Descriptions/Derived/AilmentReceiver.h"

#pragma warning(disable: 4458)

FString USwarmStatus::getStatusName() const
{
	return "Swarm";
}

int32 USwarmStatus::calculateUnderStatusEffect() const
{
	return FMath::Max<int32>(1, StaticCast<int32>(this->getThreshold() / percentsPerSatellite));
}

void USwarmStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USwarmStatus, baseThreshold);

	DOREPLIFETIME(USwarmStatus, thresholdPerTotalLifePercentPool);
	
	DOREPLIFETIME(USwarmStatus, percentsPerSatellite);

	DOREPLIFETIME(USwarmStatus, threshold);

	DOREPLIFETIME(USwarmStatus, additionalDamage);
}

void USwarmStatus::increaseThreshold(IDamageInflictor* inflictor)
{
	threshold += target->getTotalLifePercentDealt(inflictor) * thresholdPerTotalLifePercentPool;
}

float USwarmStatus::getThreshold() const
{
	return threshold;
}

void USwarmStatus::applyStatus_Implementation(const TScriptInterface<IAilmentInflictor>& inflictor, const TScriptInterface<IAilmentReceiver>& target, const FHitResult& hit)
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	for (const auto& status : statuses)
	{
		USwarmStatus* swarm = Cast<USwarmStatus>(status);

		if (swarm)
		{
			swarm->increaseThreshold(StaticCast<IAilmentInflictor*>(inflictor.GetInterface()));
			
			swarm->refreshDuration();

			target->setUnderStatusIntVariable(this->getStatusCountKey(), this->calculateUnderStatusEffect());

			return;
		}
	}

	Super::applyStatus_Implementation(inflictor, target, hit);

	target->applySwarmStatus(this);
}

void USwarmStatus::setInflictorDamage_Implementation(float newDamage)
{
	inflictorDamage = newDamage;
}

void USwarmStatus::setAdditionalInflictorDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
}

float USwarmStatus::getInflictorDamage() const
{
	return inflictorDamage;
}

float USwarmStatus::getAdditionalInflictorDamage() const
{
	return additionalDamage;
}
