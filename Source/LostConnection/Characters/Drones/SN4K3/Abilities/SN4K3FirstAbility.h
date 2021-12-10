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
	float additionalDamage;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3FirstAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	UFUNCTION(Server, Reliable)
	void setBaseDamage(float newDamage) override;

	UFUNCTION(Server, Reliable)
	void setAdditionalDamage(float newAdditionalDamage) override;

	float getBaseDamage() const override;

	float getAdditionalDamage() const override;

	typeOfDamage getDamageType() const override;

	float getCrushingHitChance() const override;

	float getAdditionalCrushingHitChance() const override;

	~USN4K3FirstAbility() = default;
};
