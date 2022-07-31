// Copyright (c) 2021 Use Your Imagination

#include "SwarmAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Characters/BaseCharacter.h"

#pragma warning(disable: 4458)

FString USwarmAilment::getStatusName() const
{
	return "Swarm";
}

int32 USwarmAilment::calculateUnderStatusEffect() const
{
	return FMath::Max<int32>(1, StaticCast<int32>(this->getThreshold() / percentsPerSatellite));
}

void USwarmAilment::onThresholdUpdate()
{
	if (TObjectPtr<ABaseCharacter> tem = Cast<ABaseCharacter>(target))
	{
		tem->updateCharacterVisualCall();
	}
}

void USwarmAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USwarmAilment, baseThreshold);

	DOREPLIFETIME(USwarmAilment, thresholdPerTotalLifePercentPool);

	DOREPLIFETIME(USwarmAilment, percentsPerSatellite);

	DOREPLIFETIME(USwarmAilment, threshold);

	DOREPLIFETIME(USwarmAilment, damageInflictorUtility);
}

USwarmAilment::USwarmAilment()
{
	damageInflictorUtility = CreateDefaultSubobject<UDamageInflictorUtility>("DamageInflictorUtility");
}

void USwarmAilment::increaseThreshold()
{
	threshold += target->getTotalLifePercentDealt(inflictor.GetObject()) * thresholdPerTotalLifePercentPool;

	this->onThresholdUpdate();
}

float USwarmAilment::getThreshold() const
{
	return threshold;
}

void USwarmAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	TScriptInterface<IAilmentReceiver> ailmentReceiver = Cast<IAilmentReceiver>(target);

	if (!ailmentReceiver)
	{
		return;
	}

	for (const TObjectPtr<UBaseStatus>& status : target->getStatuses())
	{
		if (TObjectPtr<USwarmAilment> swarm = Cast<USwarmAilment>(status))
		{
			this->inflictor = inflictor;

			swarm->refreshDuration();

			swarm->increaseThreshold();

			target->setUnderStatusIntVariable
			(
				this->getStatusCountKey(),
				this->calculateUnderStatusEffect()
			);
			
			return;
		}
	}

	Super::applyStatus_Implementation(inflictor, target, hit);

	ailmentReceiver->applySwarmAilment(this);

	threshold = baseThreshold;

	this->onThresholdUpdate();
}

void USwarmAilment::postRemove()
{
	Super::postRemove();

	threshold = 0.0f;

	this->onThresholdUpdate();
}

bool USwarmAilment::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInflictorUtility, *Bunch, *RepFlags);

	wroteSomething |= damageInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

UDamageInflictorUtility* USwarmAilment::getDamageInflictorUtility() const
{
	return damageInflictorUtility;
}

ETypeOfDamage USwarmAilment::getAilmentDamageType() const
{
	return ETypeOfDamage::nanite;
}
