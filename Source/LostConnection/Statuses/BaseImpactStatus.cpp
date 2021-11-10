#include "BaseImpactStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

void UBaseImpactStatus::applyStatus_Implementation(const TScriptInterface<IStatusReceiver>& target, const FVector& location)
{
	Super::applyStatus(target, location);

	this->applyEffect(static_cast<IStatusReceiver*>(target.GetInterface()));
}
