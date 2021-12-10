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

void UIrradiationAilment::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	if (!target->_getUObject()->Implements<UAilmentReceiver>())
	{
		return;
	}

	Super::applyStatus_Implementation(inflictor, target, hit);
}

void UIrradiationAilment::setInflictorDamage_Implementation(float newDamage)
{
	damage = newDamage;
}

void UIrradiationAilment::setAdditionalInflictorDamage_Implementation(float newAdditionalDamage)
{
	newAdditionalDamage = newAdditionalDamage;
}

float UIrradiationAilment::getBaseDamage() const
{
	return damage;
}

float UIrradiationAilment::getAdditionalDamage() const
{
	return additionalDamage;
}

typeOfDamage UIrradiationAilment::getAilmentDamageType() const
{
	return typeOfDamage::radiation;
}
