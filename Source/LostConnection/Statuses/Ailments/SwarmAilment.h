// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"
#include "Interfaces/Holders/DamageInflictorHolder.h"

#include "SwarmAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmAilment :
	public UBaseStatus,
	public IDamageInflictorHolder,
	public IAilment
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

	int32 calculateUnderStatusEffect() const override;

private:
	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float baseThreshold;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float thresholdPerTotalLifePercentPool;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float percentsPerSatellite;

	UPROPERTY(Category = Swarm, ReplicatedUsing = onThresholdUpdate, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float threshold;

	UPROPERTY(Category = Swarm, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UDamageInflictorUtility> damageInflictorUtility;

private:
	UFUNCTION()
	void onThresholdUpdate();

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USwarmAilment();

	void increaseThreshold();

	float getThreshold() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	void postRemove() override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UDamageInflictorUtility* getDamageInflictorUtility() const override;

	ETypeOfDamage getAilmentDamageType() const override;

	~USwarmAilment() = default;
};
