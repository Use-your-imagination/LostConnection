// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Statuses/BaseTickStatus.h"
#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "BurnStatus.generated.h"

UCLASS()
class LOSTCONNECTION_API UBurnStatus :
	public UBaseTickStatus,
	public IDamageInflictor
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
	UBurnStatus() = default;

	float getAdditionalFireCrushingHitChance() const;

	void applyStatus_Implementation(const TScriptInterface<IAilmentInflictor>& inflictor, const TScriptInterface<class IAilmentReceiver>& target, const FHitResult& hit) override;

	bool applyEffect(class IAilmentReceiver* target, const FHitResult& hit) override;

	UFUNCTION(Server, Reliable)
	void setInflictorDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalInflictorDamage(float newAdditionalDamage) override;

	float getInflictorDamage() const override;

	float getAdditionalInflictorDamage() const override;

	virtual ~UBurnStatus() = default;
};
