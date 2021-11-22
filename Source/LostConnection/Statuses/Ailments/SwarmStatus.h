#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"

#include "SwarmStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmStatus : public UBaseStatus
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

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

	virtual void increaseThreshold(float inflictorDamage) final;

	virtual float getThreshold() const;

	virtual void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) final override;

	virtual ~USwarmStatus() = default;
};
