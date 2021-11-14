#pragma once

#include "CoreMinimal.h"

#include "BaseTickStatus.h"

#include "SwarmStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmStatus : public UBaseTickStatus
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float poisonDamageCoefficient;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageToStacksCoefficient;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float limitDamageToStacksCoefficient;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float stacksToThresholdCoefficient;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float rampUpCoefficient;

	UPROPERTY(Category = Swarm, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float percentsPerSatellite;

	UPROPERTY(Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float poisonDamage;

	UPROPERTY(Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float stacks;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USwarmStatus() = default;

	void increaseStacks(float damage);

	float getThreshold() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) final override;

	void applyEffect(class IStatusReceiver* target, const FHitResult& hit) final override;

	virtual ~USwarmStatus() = default;
};
