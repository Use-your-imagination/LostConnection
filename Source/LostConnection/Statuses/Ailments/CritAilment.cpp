// Copyright (c) 2021 Use-your-imagination

#include "CritAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UCritAilment::getStatusName() const
{
	return "Crit";
}

SIZE_T UCritAilment::getActiveStatusesCount() const
{
	return Utility::countStatuses(target, StaticClass());
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
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	for (const UBaseStatus* status : statuses)
	{
		if (const UCritAilment* crit = Cast<UCritAilment>(status))
		{
			damageMultiplierPercent += crit->getCritMultiplier();
		}
	}

	damageInflictorUtility->setBaseDamage(inflictorDamage * Utility::fromPercent(damageMultiplierPercent));
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

bool UCritAilment::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	this->initDamage();

	target->takeDamageFromInflictorHolder(this);

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
