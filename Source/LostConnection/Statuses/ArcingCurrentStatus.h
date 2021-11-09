#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "ArcingCurrentStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UArcingCurrentStatus : public UBaseStatus
{
	GENERATED_BODY()
	
public:
	UArcingCurrentStatus() = default;

	~UArcingCurrentStatus() = default;
};
