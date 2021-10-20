#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseUltimateAbility.h"

#include "SN4K3UltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3UltimateAbility : public UBaseUltimateAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = "SN4K3|Ultimate ability", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	bool isUltimateAbilityUsed;

	UPROPERTY(Category = AbilityStats, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float abilityDuration;

	UPROPERTY(Category = "SN4K3|Ultimate ability", Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float currentAbilityDuration;

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const final override;

public:
	USN4K3UltimateAbility();

	bool getIsUltimateAbilityUsed() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void Tick(float DeltaTime) override;

	~USN4K3UltimateAbility() = default;
};

inline bool USN4K3UltimateAbility::getIsUltimateAbilityUsed() const
{
	return isUltimateAbilityUsed;
}
