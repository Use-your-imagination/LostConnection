#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Statuses/BaseStatus.h"

#include "StatusReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UStatusReceiver : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IStatusReceiver
{
	GENERATED_BODY()

public:
	IStatusReceiver() = default;

	virtual void addStatus(class UBaseStatus* status) = 0;

	virtual const TArray<UBaseStatus*>& getStatuses() const = 0;
};
