// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Derived/StatusInflictor.h"

#include "SN4K3FirstAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3FirstAbility :
	public UBaseAbility,
	public IStatusInflictor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = AbilityStats, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float damage;

	UPROPERTY(Category = AbilityStats, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float distance;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3FirstAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	float getInflictorDamage() const override;

	typeOfDamage getDamageType() const override;

	float getCrushingHitChance() const override;

	float getAdditionalCrushingHitChance() const override;

	~USN4K3FirstAbility() = default;
};
