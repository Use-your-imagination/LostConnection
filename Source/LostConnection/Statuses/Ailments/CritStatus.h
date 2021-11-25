// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseImpactStatus.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "CritStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritStatus : 
	public UBaseImpactStatus,
	public IDamageInflictor
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

	UPROPERTY(Category = Crit, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalDamage;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UCritStatus() = default;

	float getCritMultiplier() const;

	bool applyEffect(class IAilmentReceiver* target, const FHitResult& hit) override;

	UFUNCTION(Server, Reliable)
	void setInflictorDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalInflictorDamage(float newAdditionalDamage) override;

	float getInflictorDamage() const override;

	float getAdditionalInflictorDamage() const override;

	virtual ~UCritStatus() = default;
};
