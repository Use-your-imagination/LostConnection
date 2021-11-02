#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "BasePassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API UBasePassiveAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	UBasePassiveAbility() = default;

	virtual void applyAbility(class ABaseCharacter* target) override;

	virtual void useAbility() override;

	virtual ~UBasePassiveAbility() = default;
};
