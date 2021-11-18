#pragma once

#include "CoreMinimal.h"

#include "BaseImpactStatus.h"

#include "IrradiationStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UIrradiationStatus : public UBaseImpactStatus
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

	virtual SIZE_T getActiveStatusesCount() const final override;

public:
	UIrradiationStatus() = default;

	virtual ~UIrradiationStatus() = default;
};
