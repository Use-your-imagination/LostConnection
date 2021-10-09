#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "SN4K3FirstAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3FirstAbility : public ABaseAbility
{
	GENERATED_BODY()

public:
	ASN4K3FirstAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	~ASN4K3FirstAbility() = default;
};
