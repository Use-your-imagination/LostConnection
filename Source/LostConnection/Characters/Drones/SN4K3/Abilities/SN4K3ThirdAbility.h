#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "SN4K3ThirdAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3ThirdAbility : public UBaseAbility
{
	GENERATED_BODY()
	
public:
	USN4K3ThirdAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void removeAbilityEffect(class ABaseCharacter* target);

	void useAbility() override;

	~USN4K3ThirdAbility() = default;
};
