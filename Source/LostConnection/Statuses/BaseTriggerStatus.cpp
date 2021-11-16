#include "BaseTriggerStatus.h"

FString UBaseTriggerStatus::getStatusName() const
{
	PURE_VIRTUAL(UBaseTriggerStatus::getStatusName, return "";);
}

void UBaseTriggerStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseTriggerStatus, isOnceTriggered);
}

bool UBaseTriggerStatus::getIsOnceTriggered() const
{
	return isOnceTriggered;
}
