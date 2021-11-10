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

	DOREPLIFETIME(UBaseStatus, period);

	DOREPLIFETIME(UBaseStatus, currentPeriod);
}

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

bool UBaseStatus::Tick(float DeltaTime, TArray<UBaseStatus*>& statusesToRemove)
{
	currentDuration += DeltaTime;
	
	if (currentDuration >= duration)
	{
		statusesToRemove.Add(this);

		return false;
	}

	currentPeriod += DeltaTime;

	if (currentPeriod >= period)
	{
		currentPeriod -= period;

		return true;
	}

	return false;
}
