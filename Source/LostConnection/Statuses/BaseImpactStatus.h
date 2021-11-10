#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "BaseImpactStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseImpactStatus : public UBaseStatus
{
	GENERATED_BODY()

public:
	UBaseImpactStatus() = default;

	virtual void applyStatus_Implementation(const TScriptInterface<class IStatusReceiver>& target, const FVector& location) override;

	virtual ~UBaseImpactStatus() = default;
};
