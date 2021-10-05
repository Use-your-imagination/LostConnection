#pragma once

#include "CoreMinimal.h"

#include "Abilities/BasePassive.h"

#include "SN4K3PassiveAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3PassiveAbility : public ABasePassiveAbility
{
	GENERATED_BODY()
	
public:
	ASN4K3PassiveAbility();

	virtual void applyAbility(class ABaseCharacter* target) final override;

	virtual void useAbility() final override;

	~ASN4K3PassiveAbility() = default;
};
