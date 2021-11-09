#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "BaseStatus.generated.h"

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class LOSTCONNECTION_API UBaseStatus : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

public:
	UBaseStatus();

	UFUNCTION(Server, Reliable)
	virtual void applyStatus(const TScriptInterface<class IStatusReceiver>& target) final;

	virtual void applyEffect(class IStatusReceiver* target) final;

	virtual void removeStatus(class IStatusReceiver* target) final;

	virtual ~UBaseStatus() = default;
};
