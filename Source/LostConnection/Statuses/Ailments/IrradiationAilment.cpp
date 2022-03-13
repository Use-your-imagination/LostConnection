// Copyright (c) 2021 Use-your-imagination

#include "IrradiationAilment.h"

#include "Algo/Accumulate.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusReceiver.h"
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

	DOREPLIFETIME(UIrradiationAilment, irradiationMultiplier);

	DOREPLIFETIME(UIrradiationAilment, irradiationMultiplierPerPercentEnergyShieldPool);

	DOREPLIFETIME(UIrradiationAilment, additionalIrradiationMultiplier);

	DOREPLIFETIME(UIrradiationAilment, increasedDamageCoefficients);

	DOREPLIFETIME(UIrradiationAilment, moreDamageCoefficients);
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

	const TArray<UBaseStatus*>& statuses = target->getStatuses();

	additionalIrradiationMultiplier = target->getEnergyShieldPercentDealt(this) / irradiationMultiplierPerPercentEnergyShieldPool;

	irradiationMultiplier += Algo::Accumulate
	(
		statuses,
		0.0f,
		[](float currentValue, const UBaseStatus* status)
		{
			const UIrradiationAilment* irradiation = Cast<UIrradiationAilment>(status);

			if (irradiation)
			{
				return currentValue + irradiation->getAdditionalIrradiationMultiplier();
			}

			return currentValue;
		}
	);

	Super::applyStatus_Implementation(inflictor, target, hit);
}

bool UIrradiationAilment::applyEffect(IStatusReceiver* target, const FHitResult& hit)
{
	if (!Super::applyEffect(target, hit))
	{
		return false;
	}

	float tem = target->getCurrentHealth() - this->calculateTotalDamage() * Utility::fromPercent(irradiationMultiplier);

	if (tem < 0.0f)
	{
		target->setCurrentHealth(0.0f);
	}
	else
	{
		target->setCurrentHealth(tem);
	}

	return true;
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
	inflictorDamage = newDamage;
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
	return inflictorDamage;
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
	return inflictorIncreaseDamageCoefficients;
}

TArray<float> UIrradiationAilment::getMoreDamageCoefficients() const
{
	return inflictorMoreDamageCoefficients;
}

ETypeOfDamage UIrradiationAilment::getAilmentDamageType() const
{
	return ETypeOfDamage::radiation;
}
