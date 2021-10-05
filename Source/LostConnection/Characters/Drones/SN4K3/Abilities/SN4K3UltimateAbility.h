#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseUltimate.h"

#include "SN4K3UltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3UltimateAbility : public ABaseUltimateAbility
{
	GENERATED_BODY()
	
public:
	ASN4K3UltimateAbility();

	virtual void applyAbility(class ABaseCharacter* target) final override;

	virtual void useAbility() final override;

	~ASN4K3UltimateAbility() = default;
};
