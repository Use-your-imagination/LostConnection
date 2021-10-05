#pragma once

#include "CoreMinimal.h"

#include "Abilities/Base.h"

#include "SN4K3FirstAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3FirstAbility : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	ASN4K3FirstAbility();

	virtual void applyAbility(class ABaseCharacter* target) final override;

	virtual void useAbility() final override;

	~ASN4K3FirstAbility() = default;
};
