// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseStatus.h"

#include "BaseImpactStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseImpactStatus : public UBaseStatus
{
	GENERATED_BODY()

protected:
	virtual FString getStatusName() const override;

	virtual SIZE_T getActiveStatusesCount() const;

public:
	UBaseImpactStatus() = default;

	virtual void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	virtual void postRemove() final;

	virtual ~UBaseImpactStatus() = default;
};
