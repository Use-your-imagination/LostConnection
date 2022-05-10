// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTriggerStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"
#include "Interfaces/Holders/DamageInflictorHolder.h"

#include "ArcingCurrentAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UArcingCurrentAilment :
	public UBaseTriggerStatus,
	public IDamageInflictorHolder,
	public IAilment
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

	int32 calculateUnderStatusEffect() const override;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Category = ArcingCurrent, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageConvertPercent;

	UPROPERTY(Category = ArcingCurrent, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageConvertPercentPerTotalLifePercentPool;

	UPROPERTY(Category = ArcingCurrent, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float radius;

	UPROPERTY(Category = ArcingCurrent, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float underStatusValueConversionCoefficient;

	UPROPERTY(Category = ArcingCurrent, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damageConversionPercent;

	UPROPERTY(Category = ArcingCurrent, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UDamageInflictorUtility* damageInflictorUtility;

public:
	UArcingCurrentAilment();

	void increaseDamageConversion(IDamageInflictor* inflictor);

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UDamageInflictorUtility* getDamageInflictorUtility() const override;

	ETypeOfDamage getAilmentDamageType() const override;

	virtual ~UArcingCurrentAilment() = default;
};
