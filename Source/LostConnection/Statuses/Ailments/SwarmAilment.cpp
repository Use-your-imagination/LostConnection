// Copyright (c) 2021 Use-your-imagination

#include "SwarmAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"

#pragma warning(disable: 4458)

FString USwarmAilment::getStatusName() const
{
	return "Swarm";
}

int32 USwarmAilment::calculateUnderStatusEffect() const
{
	return FMath::Max<int32>(1, StaticCast<int32>(this->getThreshold() / percentsPerSatellite));
}

void USwarmAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USwarmAilment, baseThreshold);

	DOREPLIFETIME(USwarmAilment, thresholdPerTotalLifePercentPool);

	DOREPLIFETIME(USwarmAilment, percentsPerSatellite);

	DOREPLIFETIME(USwarmAilment, threshold);
}

void USwarmAilment::increaseThreshold(IDamageInflictor* inflictor)
{
	threshold += target->getTotalLifePercentDealt(inflictor) * thresholdPerTotalLifePercentPool;
}

float USwarmAilment::getThreshold() const
{
	return threshold;
}

void USwarmAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	const TArray<UBaseStatus*>& statuses = target->getStatuses();
	IAilmentReceiver* ailmentReceiver = StaticCast<IAilmentReceiver*>(target.GetInterface());

	for (const auto& status : statuses)
	{
		USwarmAilment* swarm = Cast<USwarmAilment>(status);

		if (swarm)
		{
			swarm->increaseThreshold(StaticCast<IStatusInflictor*>(inflictor.GetInterface()));

			swarm->refreshDuration();

			target->setUnderStatusIntVariable(this->getStatusCountKey(), this->calculateUnderStatusEffect());

			return;
		}
	}

	Super::applyStatus_Implementation(inflictor, target, hit);

	ailmentReceiver->applySwarmAilment(this);

	threshold = baseThreshold;
}

void USwarmAilment::setBaseDamage_Implementation(float newDamage)
{
	inflictorDamage = newDamage;
}

float USwarmAilment::getBaseDamage() const
{
	return inflictorDamage;
}

float USwarmAilment::getAddedDamage() const
{
	return 0.0f;
}

TArray<float> USwarmAilment::getIncreasedDamageCoefficients() const
{
	return {};
}

TArray<float> USwarmAilment::getMoreDamageCoefficients() const
{
	return {};
}

float USwarmAilment::getAdditionalDamage() const
{
	return 0.0f;
}

typeOfDamage USwarmAilment::getAilmentDamageType() const
{
	return typeOfDamage::nanite;
}