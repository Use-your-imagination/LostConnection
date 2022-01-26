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

	DOREPLIFETIME(USwarmAilment, increasedDamageCoefficients);

	DOREPLIFETIME(USwarmAilment, moreDamageCoefficients);
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

void USwarmAilment::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void USwarmAilment::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void USwarmAilment::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void USwarmAilment::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void USwarmAilment::setBaseDamage_Implementation(float newDamage)
{
	inflictorDamage = newDamage;
}

void USwarmAilment::setAddedDamage_Implementation(float newAddedDamage)
{
	inflictorAddedDamage = newAddedDamage;
}

void USwarmAilment::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	inflictorAdditionalDamage = newAdditionalDamage;
}

float USwarmAilment::getBaseDamage() const
{
	return inflictorDamage;
}

float USwarmAilment::getAddedDamage() const
{
	return inflictorAddedDamage;
}

float USwarmAilment::getAdditionalDamage() const
{
	return inflictorAdditionalDamage;
}

TArray<float> USwarmAilment::getIncreasedDamageCoefficients() const
{
	return increasedDamageCoefficients;
}

TArray<float> USwarmAilment::getMoreDamageCoefficients() const
{
	return moreDamageCoefficients;
}

typeOfDamage USwarmAilment::getAilmentDamageType() const
{
	return typeOfDamage::nanite;
}
