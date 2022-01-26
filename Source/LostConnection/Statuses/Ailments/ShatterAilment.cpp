// Copyright (c) 2022 Use-your-imagination

#include "ShatterAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UShatterAilment::getStatusName() const
{
	return "Shatter";
}

int32 UShatterAilment::calculateUnderStatusEffect() const
{
	return FMath::CeilToInt(duration * 2.0f);
}

void UShatterAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UShatterAilment, durationConversionPercent);

	DOREPLIFETIME(UShatterAilment, damagePercentPerMeter);

	DOREPLIFETIME(UShatterAilment, increasedDamageCoefficients);

	DOREPLIFETIME(UShatterAilment, moreDamageCoefficients);
}

void UShatterAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);

	duration = target->getTotalLifePercentDealt(inflictor) / Utility::fromPercent(durationConversionPercent);

	previousLocation = Cast<AActor>(target.GetObject())->GetActorLocation();
}

bool UShatterAilment::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	targetTotalLifePool = target->getTotalLifePool();

	target->takeDamage(this);

	previousLocation = Cast<AActor>(target->_getUObject())->GetActorLocation();

	return true;
}

bool UShatterAilment::Tick(float DeltaTime)
{
	tickPeriod = DeltaTime;

	return Super::Tick(DeltaTime);
}

void UShatterAilment::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void UShatterAilment::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void UShatterAilment::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void UShatterAilment::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void UShatterAilment::setBaseDamage_Implementation(float newDamage)
{
	damagePercentPerMeter = newDamage;
}

void UShatterAilment::setAddedDamage_Implementation(float newAddedDamage)
{
	
}

void UShatterAilment::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	
}

float UShatterAilment::getBaseDamage() const
{
	return targetTotalLifePool * Utility::fromPercent((Cast<AActor>(target->_getUObject())->GetActorLocation() - previousLocation).Size() * damagePercentPerMeter);
}

float UShatterAilment::getAddedDamage() const
{
	return 0.0f;
}

float UShatterAilment::getAdditionalDamage() const
{
	return 0.0f;
}

TArray<float> UShatterAilment::getIncreasedDamageCoefficients() const
{
	return increasedDamageCoefficients;
}

TArray<float> UShatterAilment::getMoreDamageCoefficients() const
{
	return moreDamageCoefficients;
}

typeOfDamage UShatterAilment::getAilmentDamageType() const
{
	return typeOfDamage::cold;
}
