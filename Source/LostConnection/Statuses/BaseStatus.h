// Copyright (c) 2021 Use Your Imagination

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

	TScriptInterface<class IStatusInflictor> inflictor;
	TScriptInterface<class IStatusReceiver> target;
	FDamageStructure* damage;

protected:
	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> onApplyStatus;

	UPROPERTY(Category = Particles, EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> onApplyEffect;

public:
	UBaseStatus() = default;

	UFUNCTION(Server, Reliable)
	virtual void applyStatus(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit);

	virtual bool applyEffect(const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit);

	virtual void postRemove();

	virtual bool Tick(float DeltaSeconds);

	void refreshDuration();

	void setDuration(float duration);

	const TObjectPtr<UNiagaraSystem>& getOnApplyStatus() const;

	const TObjectPtr<UNiagaraSystem>& getOnApplyEffect() const;

	float getCurrentDuration() const;

	float getRemainingDuration() const;

	virtual ~UBaseStatus() = default;
};
