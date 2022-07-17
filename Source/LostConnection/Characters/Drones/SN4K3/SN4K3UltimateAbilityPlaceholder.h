// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "WorldPlaceables/DroppedObject.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Abilities/SN4K3UltimateAbility.h"
#include "Interfaces/Gameplay/Descriptions/AITargeted.h"

#include "SN4K3UltimateAbilityPlaceholder.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LOSTCONNECTION_API ASN4K3UltimateAbilityPlaceholder : 
	public ADroppedObject,
	public IShotThrough,
	public IAITargeted
{
	GENERATED_BODY()

private:
	TObjectPtr<USN4K3UltimateAbility> ability;

public:
	ASN4K3UltimateAbilityPlaceholder();

	void setAbility(TObjectPtr<USN4K3UltimateAbility> ability);

	void impactAction_Implementation(class AAmmo* ammo, const FHitResult& hit) override;

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	bool getIsAlly() const override;

	~ASN4K3UltimateAbilityPlaceholder() = default;
};
