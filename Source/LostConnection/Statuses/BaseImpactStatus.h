// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

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

	virtual void applyStatus_Implementation(const TScriptInterface<IAilmentInflictor>& inflictor, const TScriptInterface<class IAilmentReceiver>& target, const FHitResult& hit) override;

	virtual void postRemove() final;

	virtual ~UBaseImpactStatus() = default;
};
