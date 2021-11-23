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
	virtual FString getStatusName() const final override;

	virtual SIZE_T getActiveStatusesCount() const final override;

private:
	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageMultiplierPercent;

	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageMultiplierPerTotalLifePercentPool;

	UPROPERTY(Category = Crit, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float multiplier;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UCritStatus() = default;

	virtual float getMultiplier() const final;

	virtual bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) final override;

	virtual float getInflictorDamage() const final override;

	virtual ~UCritStatus() = default;
};
