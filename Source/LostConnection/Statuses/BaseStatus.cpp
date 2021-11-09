#include "BaseStatus.h"

#include "Interfaces/Gameplay/Descriptions/StatusReceiver.h"

UBaseStatus::UBaseStatus()
{

}

void UBaseStatus::applyStatus(IStatusReceiver* target)
{
	PURE_VIRTUAL(UBaseStatus::applyStatus);
}
