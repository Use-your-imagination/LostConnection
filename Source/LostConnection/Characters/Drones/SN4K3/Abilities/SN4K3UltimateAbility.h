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

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void Tick(float DeltaTime) override;

	~USN4K3UltimateAbility() = default;
};
