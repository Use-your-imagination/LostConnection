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
}

void UIrradiationAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);
}

void UIrradiationAilment::setBaseDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

float UIrradiationAilment::getBaseDamage() const
{
	return damage;
}

float UIrradiationAilment::getAddedDamage() const
{
	return 0.0f;
}

TArray<float> UIrradiationAilment::getIncreasedDamageCoefficients() const
{
	return {};
}

TArray<float> UIrradiationAilment::getMoreDamageCoefficients() const
{
	return {};
}

float UIrradiationAilment::getAdditionalDamage() const
{
	return 0.0f;
}

typeOfDamage UIrradiationAilment::getAilmentDamageType() const
{
	return typeOfDamage::radiation;
}
