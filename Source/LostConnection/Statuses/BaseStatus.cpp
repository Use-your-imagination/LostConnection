#include "BaseStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

bool UBaseStatus::IsSupportedForNetworking() const
{
	return true;
}

void UBaseStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseStatus, duration);

	DOREPLIFETIME(UBaseStatus, currentDuration);
}

void UBaseStatus::applyStatus_Implementation(const TScriptInterface<IStatusReceiver>& target)
{
	this->target = static_cast<IStatusReceiver*>(target.GetInterface());

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

bool UBaseStatus::Tick(float DeltaTime)
{
	currentDuration += DeltaTime;
	
	if (currentDuration >= duration)
	{
		return false;
	}

	return true;
}
