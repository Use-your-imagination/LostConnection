#pragma once

#include "CoreMinimal.h"

#include "WorldPlaceables/DroppedObject.h"
#include "Interfaces/Gameplay/Descriptions/ShotThrough.h"
#include "Characters/Drones/SN4K3/Abilities/SN4K3UltimateAbility.h"

#include "SN4K3UltimateAbilityPlaceholder.generated.h"

UCLASS()
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

	float getFlatDamageReduction_Implementation() const override;

	float getPercentageDamageReduction_Implementation() const override;

	void impactAction_Implementation(class ABaseAmmo* ammo) override;

	~ASN4K3UltimateAbilityPlaceholder() = default;
};