// Copyright (c) 2021 Use Your Imagination

#include "BaseImpactStatus.h"

#include "Interfaces/Gameplay/Statuses/Base/AilmentReceiver.h"
#include "Utility/Utility.h"

FString UBaseImpactStatus::getStatusName() const
{
	PURE_VIRTUAL(UBaseImpactStatus::getStatusName, return "";);
}

int32 UBaseImpactStatus::getActiveStatusesCount() const
{
	return Utility::countStatuses(target, GetClass());
}

void UBaseImpactStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus_Implementation(inflictor, target, hit);

	this->applyEffect(target, hit);
}

void UBaseImpactStatus::postRemove()
{
	target->setUnderStatusIntVariable
	(
		this->getStatusCountKey(),
		this->getActiveStatusesCount()
	);
}
