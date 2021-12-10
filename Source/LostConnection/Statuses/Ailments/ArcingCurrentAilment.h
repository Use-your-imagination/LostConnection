// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTriggerStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "ArcingCurrentAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UArcingCurrentAilment :
	public UBaseTriggerStatus,
	public IDamageInflictor,
	public IAilment
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

	int32 calculateUnderStatusEffect() const override;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	float damageConversion;

	UPROPERTY(Category = ArcingCurrent, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalDamage;

public:
	UArcingCurrentAilment() = default;

	void increaseDamageConversion(IDamageInflictor* inflictor);

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalDamage(float newAdditionalDamage) override;

	float getBaseDamage() const override;

	float getAdditionalDamage() const override;

	typeOfDamage getAilmentDamageType() const override;

	virtual ~UArcingCurrentAilment() = default;
};
