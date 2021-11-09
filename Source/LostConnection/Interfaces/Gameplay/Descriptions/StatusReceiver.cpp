#include "StatusReceiver.h"

#include "Statuses/BaseStatus.h"

void IStatusReceiver::addStatus(UBaseStatus* status)
{
	const_cast<TArray<UBaseStatus*>&>(this->getStatuses()).Add(status);
}
