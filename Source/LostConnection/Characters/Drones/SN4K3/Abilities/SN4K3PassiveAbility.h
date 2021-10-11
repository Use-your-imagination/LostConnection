#pragma once

#include "CoreMinimal.h"

#include "Abilities/BasePassiveAbility.h"

#include "SN4K3PassiveAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3PassiveAbility : public UBasePassiveAbility
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
	USN4K3PassiveAbility();

	void resetLastTimeAbilityUsed();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void Tick(float DeltaTime) override;

	~USN4K3PassiveAbility() = default;
};
