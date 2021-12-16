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

	DOREPLIFETIME(UBurnAilment, increasedDamageCoefficients);

	DOREPLIFETIME(UBurnAilment, moreDamageCoefficients);
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

void UBurnAilment::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void UBurnAilment::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void UBurnAilment::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void UBurnAilment::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void UBurnAilment::setBaseDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UBurnAilment::setAddedDamage_Implementation(float newAddedDamage)
{
	inflictorAddedDamage = newAddedDamage;
}

void UBurnAilment::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	inflictorAdditionalDamage = newAdditionalDamage;
}

float UBurnAilment::getBaseDamage() const
{
	return damage;
}

float UBurnAilment::getAddedDamage() const
{
	return inflictorAddedDamage;
}

float UBurnAilment::getAdditionalDamage() const
{
	return inflictorAdditionalDamage;
}

TArray<float> UBurnAilment::getIncreasedDamageCoefficients() const
{
	return {};
}

TArray<float> UBurnAilment::getMoreDamageCoefficients() const
{
	return {};
}

typeOfDamage UBurnAilment::getAilmentDamageType() const
{
	return typeOfDamage::fire;
}
