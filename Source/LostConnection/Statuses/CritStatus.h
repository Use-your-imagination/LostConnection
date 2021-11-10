#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "CritStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritStatus : public UBaseStatus
{
	GENERATED_BODY()
	
public:
	UCritStatus() = default;

	virtual ~UCritStatus() = default;
};
