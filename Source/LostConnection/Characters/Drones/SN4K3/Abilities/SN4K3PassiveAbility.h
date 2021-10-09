#pragma once

#include "CoreMinimal.h"

#include "Abilities/BasePassiveAbility.h"

#include "SN4K3PassiveAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API ASN4K3PassiveAbility : public ABasePassiveAbility
{
	GENERATED_BODY()

private:
	enum class directionTypes
	{
		up,
		down
	};

private:
	float lastTimeAbilityUsed;

	directionTypes type;
	
public:
	ASN4K3PassiveAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void resetLastTimeAbilityUsed();

	~ASN4K3PassiveAbility() = default;
};
