// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTriggerStatus.h"

#include "ArcingCurrentStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UArcingCurrentStatus :
	public UBaseTriggerStatus,
	public IDamageInflictor
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
	UArcingCurrentStatus() = default;

	void increaseDamageConversion(IDamageInflictor* inflictor);

	void applyStatus_Implementation(const TScriptInterface<IAilmentInflictor>& inflictor, const TScriptInterface<class IAilmentReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IAilmentReceiver* target, const FHitResult& hit) override;

	UFUNCTION(Server, Reliable)
	void setInflictorDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalInflictorDamage(float newAdditionalDamage) override;

	float getInflictorDamage() const override;

	float getAdditionalInflictorDamage() const override;

	virtual ~UArcingCurrentStatus() = default;
};
