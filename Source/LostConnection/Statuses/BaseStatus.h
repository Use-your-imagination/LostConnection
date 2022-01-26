// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraSystem.h"

#include "Interfaces/Gameplay/Statuses/Base/StatusInflictor.h"
#include "Network/NetworkObject.h"

#include "BaseStatus.generated.h"

#pragma warning(disable: 4458)

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API UBaseStatus : public UNetworkObject
{
	GENERATED_BODY()

protected:
	FString getStatusCountKey() const;

protected:
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
	TArray<float> inflictorMoreDamageCoefficients;
	TArray<float> inflictorIncreaseDamageCoefficients;

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

	void refreshDuration();

	void setDuration(float duration);

	UNiagaraSystem* getOnApplyStatus() const;

	UNiagaraSystem* getOnApplyEffect() const;

	float getCurrentDuration() const;

	float getRemainingDuration() const;

	virtual ~UBaseStatus() = default;
};
