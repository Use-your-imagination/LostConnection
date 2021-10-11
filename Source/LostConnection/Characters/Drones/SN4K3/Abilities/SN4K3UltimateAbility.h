#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseUltimateAbility.h"

#include "SN4K3UltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3UltimateAbility : public UBaseUltimateAbility
{
	GENERATED_BODY()
	
private:
	float abilityDuration;
	float currentAbilityDuration;

public:
	USN4K3UltimateAbility();

	void Tick(float DeltaTime) override;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	~USN4K3UltimateAbility() = default;
};
