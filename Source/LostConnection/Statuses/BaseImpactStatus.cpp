#include "BaseImpactStatus.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

void UBaseImpactStatus::applyStatus_Implementation(ABaseCharacter* causer, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus_Implementation(causer, target, hit);

	this->applyEffect(static_cast<IStatusReceiver*>(target.GetInterface()), hit);
}
