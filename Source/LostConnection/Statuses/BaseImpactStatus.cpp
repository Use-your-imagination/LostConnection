// Copyright (c) 2021 Use-your-imagination

#include "BaseImpactStatus.h"

#include "Interfaces/Gameplay/Descriptions/Derived/AilmentReceiver.h"

FString UBaseImpactStatus::getStatusName() const
{
	PURE_VIRTUAL(UBaseImpactStatus::getStatusName, return "";);
}

SIZE_T UBaseImpactStatus::getActiveStatusesCount() const
{
	PURE_VIRTUAL(UBaseImpactStatus::getActiveStatusesCount, return 0;);
}

void UBaseImpactStatus::applyStatus_Implementation(const TScriptInterface<IAilmentInflictor>& inflictor, const TScriptInterface<IAilmentReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus_Implementation(inflictor, target, hit);

	this->applyEffect(StaticCast<IAilmentReceiver*>(target.GetInterface()), hit);
}

void UBaseImpactStatus::postRemove()
{
	target->setUnderStatusIntVariable
	(
		this->getStatusCountKey(),
		this->getActiveStatusesCount()
	);
}
