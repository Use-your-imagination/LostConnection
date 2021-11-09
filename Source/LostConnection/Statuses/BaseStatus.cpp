#include "BaseStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

UBaseStatus::UBaseStatus()
{

}

void UBaseStatus::applyStatus_Implementation(const TScriptInterface<IStatusReceiver>& target)
{
	target->addStatus(this);
}

void UBaseStatus::applyEffect(IStatusReceiver* target)
{
	PURE_VIRTUAL(UBaseStatus::applyEffect);
}

void UBaseStatus::removeStatus(IStatusReceiver* target)
{
	const_cast<TArray<UBaseStatus*>&>(target->getStatuses()).Remove(this);
}
