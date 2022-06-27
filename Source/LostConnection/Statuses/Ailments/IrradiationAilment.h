// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseImpactStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"
#include "Interfaces/Holders/DamageInflictorHolder.h"

#include "IrradiationAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UIrradiationAilment :
	public UBaseImpactStatus,
	public IDamageInflictorHolder,
	public IAilment
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = Irradiation, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float irradiationMultiplier;

	UPROPERTY(Category = Irradiation, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float irradiationMultiplierPerPercentEnergyShieldPool;

	UPROPERTY(Category = Irradiation, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalIrradiationMultiplier;

	UPROPERTY(Category = Irradiation, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UDamageInflictorUtility* damageInflictorUtility;

private:
	FString getStatusName() const override;

	int32 getActiveStatusesCount() const override;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void initDamage();

public:
	UIrradiationAilment();

	float getAdditionalIrradiationMultiplier() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UDamageInflictorUtility* getDamageInflictorUtility() const override;

	ETypeOfDamage getAilmentDamageType() const override;

	~UIrradiationAilment() = default;
};
