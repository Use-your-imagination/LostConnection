#pragma once

#include "CoreMinimal.h"

#include "BaseImpactStatus.h"

#include "CritStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritStatus : public UBaseImpactStatus
{
	GENERATED_BODY()
	
public:
	UCritStatus() = default;

	virtual ~UCritStatus() = default;
};
