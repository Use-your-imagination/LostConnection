// Copyright (c) 2021 Use Your Imagination

#include "CritAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UCritAilment::getStatusName() const
{
	return "Crit";
}

void UCritAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCritAilment, damageMultiplierPercent);

	DOREPLIFETIME(UCritAilment, damageMultiplierPerTotalLifePercentPool);

	DOREPLIFETIME(UCritAilment, critMultiplier);

	DOREPLIFETIME(UCritAilment, damageInflictorUtility);
}

void UCritAilment::initDamage()
{
	const TArray<TObjectPtr<UBaseStatus>>& statuses = target->getStatuses();

	for (const TObjectPtr<UBaseStatus>& status : statuses)
	{
		if (TObjectPtr<UCritAilment> crit = Cast<UCritAilment>(status))
		{
			damageMultiplierPercent += crit->getCritMultiplier();
		}
	}

	damageInflictorUtility->getDamage().baseDamage = damage.baseDamage * Utility::fromPercent(damageMultiplierPercent);
}

UCritAilment::UCritAilment()
{
	damageInflictorUtility = CreateDefaultSubobject<UDamageInflictorUtility>("DamageInflictorUtility");
}

float UCritAilment::getCritMultiplier() const
{
	return critMultiplier;
}

void UCritAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);
}

bool UCritAilment::applyEffect(const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	this->initDamage();

	target->takeDamageFromInflictorHolder(this);

	Utility::resetDamageInflictor(damageInflictorUtility);

	damageInflictorUtility->getDamage().baseDamage = damage.baseDamage;

	critMultiplier = target->getTotalLifePercentDealt(this) * damageMultiplierPerTotalLifePercentPool;

	return true;
}

bool UCritAilment::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInflictorUtility, *Bunch, *RepFlags);

	wroteSomething |= damageInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

UDamageInflictorUtility* UCritAilment::getDamageInflictorUtility() const
{
	return damageInflictorUtility;
}

ETypeOfDamage UCritAilment::getAilmentDamageType() const
{
	return ETypeOfDamage::physical;
}
