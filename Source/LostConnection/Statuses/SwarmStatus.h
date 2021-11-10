#pragma once

#include "CoreMinimal.h"

#include "BaseTickStatus.h"

#include "SwarmStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmStatus : public UBaseTickStatus
{
	GENERATED_BODY()
	
public:
	USwarmStatus() = default;

	virtual ~USwarmStatus() = default;
};
