#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "SwarmStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmStatus : public UBaseStatus
{
	GENERATED_BODY()
	
public:
	USwarmStatus() = default;

	virtual ~USwarmStatus() = default;
};
