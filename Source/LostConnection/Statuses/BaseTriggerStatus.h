#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "BaseTriggerStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseTriggerStatus : public UBaseStatus
{
	GENERATED_BODY()

public:
	UBaseTriggerStatus() = default;

	virtual ~UBaseTriggerStatus() = default;
};
