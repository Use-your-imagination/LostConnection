#include "BaseImpactStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

void UBaseImpactStatus::applyStatus_Implementation(const TScriptInterface<IStatusReceiver>& target)
{
	Super::applyStatus(target);

	this->applyEffect(static_cast<IStatusReceiver*>(target.GetInterface()));
}
