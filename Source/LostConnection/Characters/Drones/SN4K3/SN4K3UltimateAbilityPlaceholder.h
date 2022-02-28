// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "WorldPlaceables/DroppedObject.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Abilities/SN4K3UltimateAbility.h"

#include "SN4K3UltimateAbilityPlaceholder.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ASN4K3UltimateAbilityPlaceholder : 
	public ADroppedObject,
	public IShotThrough
{
	GENERATED_BODY()

private:
	USN4K3UltimateAbility* ability;

public:
	ASN4K3UltimateAbilityPlaceholder();

	void setAbility(USN4K3UltimateAbility* ability);

	void impactAction_Implementation(class AAmmo* ammo, const FHitResult& hit) override;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	virtual ~ASN4K3UltimateAbilityPlaceholder() = default;
};
