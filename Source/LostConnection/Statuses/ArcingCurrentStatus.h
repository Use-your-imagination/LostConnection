#pragma once

#include "CoreMinimal.h"

#include "BaseTriggerStatus.h"

#include "ArcingCurrentStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UArcingCurrentStatus : public UBaseTriggerStatus
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

public:
	UArcingCurrentStatus() = default;

	virtual ~UArcingCurrentStatus() = default;
};
