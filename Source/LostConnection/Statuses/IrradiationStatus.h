#pragma once

#include "CoreMinimal.h"

#include "BaseImpactStatus.h"

#include "IrradiationStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UIrradiationStatus : public UBaseImpactStatus
{
	GENERATED_BODY()
	
public:
	UIrradiationStatus() = default;

	virtual ~UIrradiationStatus() = default;
};
