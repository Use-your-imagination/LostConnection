#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "IrradiationStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UIrradiationStatus : public UBaseStatus
{
	GENERATED_BODY()
	
public:
	UIrradiationStatus() = default;

	virtual ~UIrradiationStatus() = default;
};
