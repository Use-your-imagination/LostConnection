// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseImpactStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "CritAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritAilment : 
	public UBaseImpactStatus,
	public IDamageInflictor,
	public IAilment
{
	GENERATED_BODY()

private:
	FString getStatusName() const override;

	SIZE_T getActiveStatusesCount() const override;

private:
	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageMultiplierPercent;

	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageMultiplierPerTotalLifePercentPool;

	UPROPERTY(Category = Crit, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float critMultiplier;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UCritAilment() = default;

	float getCritMultiplier() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage) override;

	float getBaseDamage() const override;

	float getAddedDamage() const override;

	TArray<float> getIncreasedDamageCoefficients() const override;

	TArray<float> getMoreDamageCoefficients() const override;

	float getAdditionalDamage() const override;

	typeOfDamage getAilmentDamageType() const override;

	virtual ~UCritAilment() = default;
};
