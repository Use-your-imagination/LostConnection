#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseUltimateAbility.h"

#include "SN4K3UltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3UltimateAbility : public ABaseUltimateAbility
{
	GENERATED_BODY()
	
public:
	ASN4K3UltimateAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	~ASN4K3UltimateAbility() = default;
};
