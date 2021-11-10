#include "BaseTickStatus.h"

void UBaseTickStatus::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBaseTickStatus, tickPeriod);

	DOREPLIFETIME(UBaseTickStatus, currentTickPeriod);
}

bool UBaseTickStatus::Tick(float DeltaTime)
{
	bool result = Super::Tick(DeltaTime);

	if (!result)
	{
		return result;
	}

	currentTickPeriod += DeltaTime;

	if (currentTickPeriod >= tickPeriod)
	{
		currentTickPeriod -= tickPeriod;

		this->applyEffect(target);
	}

	return true;
}
