// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "SwarmStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmStatus :
	public UBaseStatus,
	public IDamageInflictor
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

	int32 calculateUnderStatusEffect() const override;

private:
	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float baseThreshold;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float thresholdPerTotalLifePercentPool;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float percentsPerSatellite;

	UPROPERTY(Category = Swarm, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float threshold;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USwarmStatus() = default;

	void increaseThreshold(IDamageInflictor* inflictor);

	float getThreshold() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	float getInflictorDamage() const override;

	virtual ~USwarmStatus() = default;
};
