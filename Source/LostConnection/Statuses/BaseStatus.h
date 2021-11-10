#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "NiagaraComponent.h"
#include "Net/UnrealNetwork.h"

#include "BaseStatus.generated.h"

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class LOSTCONNECTION_API UBaseStatus : public UObject
{
	GENERATED_BODY()

protected:
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float duration;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	float currentDuration;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float period;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	float currentPeriod;

private:
	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* onHit;

	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* onTick;

	UPROPERTY(Category = Components, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* underStatus;

public:
	UBaseStatus();

	UFUNCTION(Server, Reliable)
	virtual void applyStatus(const TScriptInterface<class IStatusReceiver>& target) final;

	virtual void applyEffect(class IStatusReceiver* target);

	virtual void removeStatus(class IStatusReceiver* target) final;

	virtual bool Tick(float DeltaTime, TArray<UBaseStatus*>& statusesToRemove) final;

	virtual ~UBaseStatus() = default;
};
