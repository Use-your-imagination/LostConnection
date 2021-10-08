#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "SN4K3ThirdAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3ThirdAbility : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	ASN4K3ThirdAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void removeAbilityEffect(class ABaseCharacter* target);

	void useAbility() override;

	~ASN4K3ThirdAbility() = default;
};
