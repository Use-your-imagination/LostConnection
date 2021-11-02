#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "SN4K3SecondAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3SecondAbility : public UBaseAbility
{
	GENERATED_BODY()

private:
	class ABaseCharacter* target;
	
	UPROPERTY(Category = "SN4K3|Second ability", EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float distance;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USN4K3SecondAbility();

	float getDistance() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	~USN4K3SecondAbility() = default;
};
