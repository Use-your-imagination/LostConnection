// Copyright (c) 2021 Use-your-imagination

#include "BurnStatus.h"

#include "Interfaces/Gameplay/Descriptions/Derived/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UBurnStatus::getStatusName() const
{
	return "Burn";
}

int32 UBurnStatus::calculateUnderStatusEffect() const
{
	return Utility::countStatuses(target, StaticClass());
}

void UBurnStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBurnStatus, burnDamageCoefficient);

	DOREPLIFETIME(UBurnStatus, additionalFireCrushingHitChance);

	DOREPLIFETIME(UBurnStatus, damage);

	DOREPLIFETIME(UBurnStatus, additionalDamage);
}

float UBurnStatus::getAdditionalFireCrushingHitChance() const
{
	return additionalFireCrushingHitChance;
}

void UBurnStatus::applyStatus_Implementation(const TScriptInterface<IAilmentInflictor>& inflictor, const TScriptInterface<IAilmentReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus_Implementation(inflictor, target, hit);

	damage = (inflictorDamage * burnDamageCoefficient) / (duration / tickPeriod);
}

bool UBurnStatus::applyEffect(IAilmentReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	target->takeDamage(this);

	return true;
}

void UBurnStatus::setInflictorDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UBurnStatus::setAdditionalInflictorDamage_Implementation(float newAdditionalDamage)
{
	additionalDamage = newAdditionalDamage;
}

float UBurnStatus::getInflictorDamage() const
{
	return damage;
}

float UBurnStatus::getAdditionalInflictorDamage() const
{
	return additionalDamage;
}
