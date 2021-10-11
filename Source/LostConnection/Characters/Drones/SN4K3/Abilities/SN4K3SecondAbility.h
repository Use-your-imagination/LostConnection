#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "SN4K3SecondAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3SecondAbility : public UBaseAbility
{
	GENERATED_BODY()
	
public:
	USN4K3SecondAbility();

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	~USN4K3SecondAbility() = default;
};
