#pragma once

#include "CoreMinimal.h"

#include "BaseTickStatus.h"
#include "Interfaces/Gameplay/Descriptions/Stackable.h"

#include "SwarmStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmStatus : 
	public UBaseTickStatus,
	public IStackable
{
	GENERATED_BODY()
	
private:
	virtual FString getStatusName() const final override;

	virtual bool increaseStacksCondition(float damage) const final override;

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

	UPROPERTY(Category = Swarm, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float poisonDamage;

	UPROPERTY(Category = Swarm, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float stacks;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USwarmStatus() = default;

	virtual float getThreshold() const;

	virtual void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) final override;

	virtual void applyEffect(class IStatusReceiver* target, const FHitResult& hit) final override;

	virtual void postRemove() final override;

	virtual float getDamageToStacksCoefficient() const final override;

	virtual float& getStacks() final override;

	virtual float getStacks() const final override;

	virtual ~USwarmStatus() = default;
};
