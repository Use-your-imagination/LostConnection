#include "BaseImpactStatus.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

void UBaseImpactStatus::applyStatus_Implementation(const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus(target, hit);

	this->applyEffect(static_cast<IStatusReceiver*>(target.GetInterface()), hit);
}
