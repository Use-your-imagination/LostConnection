// Copyright (c) 2021 Use Your Imagination

#include "BaseImpactStatus.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"

FString UBaseImpactStatus::getStatusName() const
{
	PURE_VIRTUAL(UBaseImpactStatus::getStatusName, return "";);
}

SIZE_T UBaseImpactStatus::getActiveStatusesCount() const
{
	PURE_VIRTUAL(UBaseImpactStatus::getActiveStatusesCount, return 0;);
}

void UBaseImpactStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus_Implementation(inflictor, target, hit);

	this->applyEffect(StaticCast<IStatusReceiver*>(target.GetInterface()), hit);
}

void UBaseImpactStatus::postRemove()
{
	target->setUnderStatusIntVariable
	(
		this->getStatusCountKey(),
		this->getActiveStatusesCount()
	);
}
