#include "BaseImpactStatus.h"

#include "Characters/BaseCharacter.h"
#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

FString UBaseImpactStatus::getStatusName() const
{
	PURE_VIRTUAL(UBaseImpactStatus::getStatusName, return "";);
}

void UBaseImpactStatus::applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target, const FHitResult& hit)
{
	Super::applyStatus_Implementation(inflictor, target, hit);

	this->applyEffect(static_cast<IStatusReceiver*>(target.GetInterface()), hit);
}
