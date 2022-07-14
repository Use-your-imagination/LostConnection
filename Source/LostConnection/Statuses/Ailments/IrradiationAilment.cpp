// Copyright (c) 2021 Use Your Imagination

#include "IrradiationAilment.h"

#include "Algo/Accumulate.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UIrradiationAilment::getStatusName() const
{
	return "Irradiation";
}

void UIrradiationAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UIrradiationAilment, irradiationMultiplier);

	DOREPLIFETIME(UIrradiationAilment, irradiationMultiplierPerPercentEnergyShieldPool);

	DOREPLIFETIME(UIrradiationAilment, additionalIrradiationMultiplier);

	DOREPLIFETIME(UIrradiationAilment, damageInflictorUtility);
}

void UIrradiationAilment::initDamage()
{
	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	for (const UBaseStatus* status : statuses)
	{
		if (const UIrradiationAilment* irradiation = Cast<UIrradiationAilment>(status))
		{
			irradiationMultiplier += irradiation->getAdditionalIrradiationMultiplier();
		}
	}

	damageInflictorUtility->getDamage().baseDamage = damage.baseDamage * Utility::fromPercent(irradiationMultiplier);
}

UIrradiationAilment::UIrradiationAilment()
{
	damageInflictorUtility = CreateDefaultSubobject<UDamageInflictorUtility>("DamageInflictorUtility");
}

float UIrradiationAilment::getAdditionalIrradiationMultiplier() const
{
	return additionalIrradiationMultiplier;
}

void UIrradiationAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);
}

bool UIrradiationAilment::applyEffect(const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	this->initDamage();

	float tem = target->getCurrentHealth() - damageInflictorUtility->calculateTotalDamage();

	if (tem < 0.0f)
	{
		target->setCurrentHealth(0.0f);
	}
	else
	{
		target->setCurrentHealth(tem);
	}

	Utility::resetDamageInflictor(damageInflictorUtility);

	damageInflictorUtility->getDamage().baseDamage = damage.baseDamage;

	additionalIrradiationMultiplier = target->getEnergyShieldPercentDealt(this) / irradiationMultiplierPerPercentEnergyShieldPool;

	return true;
}

bool UIrradiationAilment::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	wroteSomething |= Channel->ReplicateSubobject(damageInflictorUtility, *Bunch, *RepFlags);

	wroteSomething |= damageInflictorUtility->ReplicateSubobjects(Channel, Bunch, RepFlags);

	return wroteSomething;
}

UDamageInflictorUtility* UIrradiationAilment::getDamageInflictorUtility() const
{
	return damageInflictorUtility;
}

ETypeOfDamage UIrradiationAilment::getAilmentDamageType() const
{
	return ETypeOfDamage::radiation;
}
