// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraSystem.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusInflictor.h"

#include "BaseStatus.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseStatus : public UObject
{
	GENERATED_BODY()

protected:
	virtual FString getStatusCountKey() const final;

protected:
	virtual bool IsSupportedForNetworking() const final override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual FString getStatusName() const;

	virtual int32 calculateUnderStatusEffect() const;

protected:
	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText name;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, BlueprintReadOnly)
	FText description;

	UPROPERTY(Category = Statuses, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float duration;

	UPROPERTY(Category = Statuses, Replicated, BlueprintReadOnly)
	float currentDuration;

	class IStatusReceiver* target;
	float inflictorDamage;
	float inflictorAddedDamage;
	float inflictorAdditionalDamage;

protected:
	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyStatus;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraSystem* onApplyEffect;

public:
	UBaseStatus() = default;

	UFUNCTION(Server, Reliable)
	virtual void applyStatus(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit);

	virtual bool applyEffect(class IStatusReceiver* target, const FHitResult& hit);

	virtual void postRemove();

	virtual bool Tick(float DeltaTime);

	virtual void refreshDuration() final;

	virtual void setDuration(float duration) final;

	virtual UNiagaraSystem* getOnApplyStatus() final;

	virtual UNiagaraSystem* getOnApplyEffect() final;

	virtual ~UBaseStatus() = default;
};
