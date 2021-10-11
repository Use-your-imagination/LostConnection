#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "SN4K3FirstAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3FirstAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	USN4K3FirstAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	~USN4K3FirstAbility() = default;
};
