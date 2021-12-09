// Copyright (c) 2021 Use-your-imagination

#include "BurnAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UBurnAilment::getStatusName() const
{
	return "Burn";
}

int32 UBurnAilment::calculateUnderStatusEffect() const
{
	return Utility::countStatuses(target, StaticClass());
}

void UBurnAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBurnAilment, burnDamageCoefficient);

	DOREPLIFETIME(UBurnAilment, additionalFireCrushingHitChance);

	DOREPLIFETIME(UBurnAilment, damage);

	DOREPLIFETIME(UBurnAilment, additionalDamage);
}

float UBurnAilment::getAdditionalFireCrushingHitChance() const
{
	return additionalFireCrushingHitChance;
}

void UBurnAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);

	damage = (inflictorDamage * burnDamageCoefficient) / (duration / tickPeriod);
}

bool UBurnAilment::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	target->takeDamage(this);

	return true;
}

void UBurnAilment::setInflictorDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UBurnAilment::setAdditionalInflictorDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
}

float UBurnAilment::getInflictorDamage() const
{
	return damage;
}

float UBurnAilment::getAdditionalInflictorDamage() const
{
	return additionalDamage;
}

typeOfDamage UBurnAilment::getAilmentDamageType() const
{
	return typeOfDamage::fire;
}
