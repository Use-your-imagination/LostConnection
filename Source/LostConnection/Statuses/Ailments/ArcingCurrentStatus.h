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

public:
	UArcingCurrentStatus() = default;

	void increaseDamageConversion(IDamageInflictor* inflictor);

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	float getInflictorDamage() const override;

	virtual ~UArcingCurrentStatus() = default;
};
