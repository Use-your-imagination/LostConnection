// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseImpactStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "CritAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritAilment : 
	public UBaseImpactStatus,
	public IAilment
{
	GENERATED_BODY()

private:
	FString getStatusName() const override;

private:
	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float damageMultiplierPercent;

	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float damageMultiplierPerTotalLifePercentPool;

	UPROPERTY(Category = Crit, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float critMultiplier;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UCritAilment() = default;

	float getCritMultiplier() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	ETypeOfDamage getAilmentDamageType() const override;

	~UCritAilment() = default;
};
