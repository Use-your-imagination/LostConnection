// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseImpactStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"
#include "Interfaces/Holders/DamageInflictorHolder.h"

#include "CritAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UCritAilment : 
	public UBaseImpactStatus,
	public IDamageInflictorHolder,
	public IAilment
{
	GENERATED_BODY()

private:
	FString getStatusName() const override;

	int32 getActiveStatusesCount() const override;

private:
	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageMultiplierPercent;

	UPROPERTY(Category = Crit, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageMultiplierPerTotalLifePercentPool;

	UPROPERTY(Category = Crit, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float critMultiplier;

	UPROPERTY(Category = Crit, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UDamageInflictorUtility* damageInflictorUtility;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void initDamage();

public:
	UCritAilment();

	float getCritMultiplier() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UDamageInflictorUtility* getDamageInflictorUtility() const override;

	ETypeOfDamage getAilmentDamageType() const override;

	~UCritAilment() = default;
};
