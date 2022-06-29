// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTickStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"
#include "Interfaces/Holders/DamageInflictorHolder.h"

#include "ShatterAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UShatterAilment :
	public UBaseTickStatus,
	public IDamageInflictorHolder,
	public IAilment
{
	GENERATED_BODY()

private:
	FString getStatusName() const override;

	int32 calculateUnderStatusEffect() const override;

private:
	UPROPERTY(Category = Shatter, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float durationConversionPercent;

	UPROPERTY(Category = Shatter, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float damagePercentPerMeter;

	UPROPERTY(Category = Shatter, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	UDamageInflictorUtility* damageInflictorUtility;

	FVector previousLocation;
	float targetTotalLifePool;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void updateDuration(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<IStatusReceiver>& target);

public:
	UShatterAilment();

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	bool Tick(float DeltaSeconds) override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UDamageInflictorUtility* getDamageInflictorUtility() const override;

	ETypeOfDamage getAilmentDamageType() const override;

	~UShatterAilment() = default;
};
