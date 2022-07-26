// Copyright (c) 2022 Use Your Imagination

#include "BaseDamagePersonalModule.h"

#include "Interfaces/Holders/AilmentInflictorHolder.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"
#include "Utility/Utility.h"

bool UBaseDamagePersonalModule::applyCondition(TObjectPtr<AActor> caller) const
{
	if (IAilmentInflictorHolder* holder = Cast<IAilmentInflictorHolder>(caller))
	{
		return this->getDamageType() == holder->getAilmentInflictorUtility()->getDamageType();
	}
	else if (IAilmentInflictor* inflictor = Cast<IAilmentInflictor>(caller))
	{
		return this->getDamageType() == inflictor->getDamageType();
	}

	return false;
}

bool UBaseDamagePersonalModule::affectCondition(const TScriptInterface<IDamageInflictor>& inflictor, const TScriptInterface<IDamageReceiver>& receiver) const
{
	return this->applyCondition(Cast<AActor>(receiver));
}

void UBaseDamagePersonalModule::affect(FDamageStructure& damage)
{
	float multiplier = this->getMultiplier();
	TArray<float> increase = moduleDamage.increaseDamageCoefficients;
	TArray<float> more = moduleDamage.moreDamageCoefficients;
	auto applyMultiplier = [multiplier](TArray<float>& coefficients)
	{
		for (auto& coefficient : coefficients)
		{
			coefficient *= multiplier;
		}
	};

	applyMultiplier(increase);
	applyMultiplier(more);

	damage.baseDamage += moduleDamage.baseDamage * multiplier;
	damage.addedDamage += moduleDamage.addedDamage * multiplier;
	damage.additionalDamage += moduleDamage.additionalDamage * multiplier;
	damage.increaseDamageCoefficients.Append(MoveTemp(increase));
	damage.moreDamageCoefficients.Append(MoveTemp(more));
}
