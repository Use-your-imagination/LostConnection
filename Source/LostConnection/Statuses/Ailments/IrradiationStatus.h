// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseImpactStatus.h"

#include "IrradiationStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UIrradiationStatus : public UBaseImpactStatus
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

	SIZE_T getActiveStatusesCount() const override;

public:
	UIrradiationStatus() = default;

	virtual ~UIrradiationStatus() = default;
};
