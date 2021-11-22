// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTriggerStatus.h"

#include "ArcingCurrentStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UArcingCurrentStatus : public UBaseTriggerStatus
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

public:
	UArcingCurrentStatus() = default;

	virtual ~UArcingCurrentStatus() = default;
};
