// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTickStatus.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "BurnAilment.generated.h"

UCLASS()
class LOSTCONNECTION_API UBurnAilment :
	public UBaseTickStatus,
	public IDamageInflictor,
	public IAilment
{
	GENERATED_BODY()
	
private:
	FString getStatusName() const override;

	int32 calculateUnderStatusEffect() const override;

private:
	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float burnDamageCoefficient;

	UPROPERTY(Category = Burn, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalFireCrushingHitChance;

	UPROPERTY(Category = Burn, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damage;

	UPROPERTY(Category = Burn, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalDamage;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBurnAilment() = default;

	float getAdditionalFireCrushingHitChance() const;

	void applyStatus_Implementation(const TScriptInterface<IStatusInflictor>& inflictor, const TScriptInterface<class IStatusReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IStatusReceiver* target, const FHitResult& hit) override;

	UFUNCTION(Server, Reliable)
	void setInflictorDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalInflictorDamage(float newAdditionalDamage) override;

	float getInflictorDamage() const override;

	float getAdditionalInflictorDamage() const override;

	typeOfDamage getAilmentDamageType() const override;

	virtual ~UBurnAilment() = default;
};
