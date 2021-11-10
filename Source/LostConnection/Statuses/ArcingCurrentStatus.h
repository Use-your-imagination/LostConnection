#pragma once

#include "CoreMinimal.h"

#include "BaseImpactStatus.h"

#include "ArcingCurrentStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UArcingCurrentStatus : public UBaseImpactStatus
{
	GENERATED_BODY()
	
public:
	UArcingCurrentStatus() = default;

	virtual ~UArcingCurrentStatus() = default;
};
