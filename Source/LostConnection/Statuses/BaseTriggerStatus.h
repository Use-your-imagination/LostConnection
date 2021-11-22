// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "BaseTriggerStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseTriggerStatus : public UBaseStatus
{
	GENERATED_BODY()

protected:
	virtual FString getStatusName() const override;

protected:
	UPROPERTY(Category = TriggerStatus, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	bool isOnceTriggered;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseTriggerStatus() = default;

	virtual bool getIsOnceTriggered() const final;

	virtual ~UBaseTriggerStatus() = default;
};
