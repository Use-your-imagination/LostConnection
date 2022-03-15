// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Statuses/Base/AilmentInflictor.h"

#include "SN4K3FirstAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3FirstAbility :
	public UBaseAbility,
	public IAilmentInflictor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damage;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float distance;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float addedDamage;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float additionalDamage;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<float> increasedDamageCoefficients;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TArray<float> moreDamageCoefficients;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3FirstAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	virtual void appendIncreasedDamageCoefficient(float coefficient) final override;

	virtual void removeIncreasedDamageCoefficient(float coefficient) final override;

	virtual void appendMoreDamageCoefficient(float coefficient) final override;

	virtual void removeMoreDamageCoefficient(float coefficient) final override;

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAddedDamage(float newAddedDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalDamage(float newAdditionalDamage) override;

	float getBaseDamage() const override;

	float getAddedDamage() const override;

	float getAdditionalDamage() const override;

	TArray<float> getIncreasedDamageCoefficients() const override;

	TArray<float> getMoreDamageCoefficients() const override;

	ETypeOfDamage getDamageType() const override;

	float getBaseCrushingHitChance() const override;

	float getAdditionalCrushingHitChance() const override;

	~USN4K3FirstAbility() = default;
};
