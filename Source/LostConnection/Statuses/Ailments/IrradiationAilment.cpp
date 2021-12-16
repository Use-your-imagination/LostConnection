// Copyright (c) 2021 Use-your-imagination

#include "IrradiationAilment.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UIrradiationAilment::getStatusName() const
{
	return "Irradiation";
}

SIZE_T UIrradiationAilment::getActiveStatusesCount() const
{
	return Utility::countStatuses(target, StaticClass());
}

void UIrradiationAilment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UIrradiationAilment, damage);
	
	DOREPLIFETIME(UIrradiationAilment, increasedDamageCoefficients);

	DOREPLIFETIME(UIrradiationAilment, moreDamageCoefficients);
}

void UIrradiationAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);
}

void UIrradiationAilment::appendIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Add(coefficient);
}

void UIrradiationAilment::removeIncreasedDamageCoefficient(float coefficient)
{
	increasedDamageCoefficients.Remove(coefficient);
}

void UIrradiationAilment::appendMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Add(coefficient);
}

void UIrradiationAilment::removeMoreDamageCoefficient(float coefficient)
{
	moreDamageCoefficients.Remove(coefficient);
}

void UIrradiationAilment::setBaseDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UIrradiationAilment::setAddedDamage_Implementation(float newAddedDamage)
{
	inflictorAddedDamage = newAddedDamage;
}

void UIrradiationAilment::setAdditionalDamage_Implementation(float newAdditionalDamage)
{
	inflictorAdditionalDamage = newAdditionalDamage;
}

float UIrradiationAilment::getBaseDamage() const
{
	return damage;
}

float UIrradiationAilment::getAddedDamage() const
{
	return inflictorAddedDamage;
}

float UIrradiationAilment::getAdditionalDamage() const
{
	return inflictorAdditionalDamage;
}

TArray<float> UIrradiationAilment::getIncreasedDamageCoefficients() const
{
	return {};
}

TArray<float> UIrradiationAilment::getMoreDamageCoefficients() const
{
	return {};
}

typeOfDamage UIrradiationAilment::getAilmentDamageType() const
{
	return typeOfDamage::radiation;
}
