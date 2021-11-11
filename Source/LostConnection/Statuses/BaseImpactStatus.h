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

	virtual void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	virtual ~UBaseImpactStatus() = default;
};
