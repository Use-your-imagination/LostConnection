#include "BaseTriggerStatus.h"

void UBaseTriggerStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseTriggerStatus, isOnceTriggered);
}

bool UBaseTriggerStatus::getIsOnceTriggered() const
{
	return isOnceTriggered;
}
