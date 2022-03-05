// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "SwarmAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API USwarmAilment :
	public UBaseStatus,
	public IDamageInflictor,
	public IAilment
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

	UPROPERTY(Category = Swarm, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<float> increasedDamageCoefficients;

	UPROPERTY(Category = Swarm, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<float> moreDamageCoefficients;

private:
	void updateSwarmHealthBar();

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USwarmAilment() = default;

	void increaseThreshold(IDamageInflictor* inflictor);

	float getThreshold() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	void postRemove() override;

	void appendIncreasedDamageCoefficient(float coefficient) override;

	void removeIncreasedDamageCoefficient(float coefficient) override;

	void appendMoreDamageCoefficient(float coefficient) override;

	void removeMoreDamageCoefficient(float coefficient) override;

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAddedDamage(float newAddedDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalDamage(float newAdditionalDamage) override;

	float getBaseDamage() const override;

	float getAddedDamage() const override;

	float getAdditionalDamage() const override;

	TArray<float> getIncreasedDamageCoefficients() const override;

	TArray<float> getMoreDamageCoefficients() const override;

	typeOfDamage getAilmentDamageType() const override;

	virtual ~USwarmAilment() = default;
};
