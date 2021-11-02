#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "SN4K3ThirdAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3ThirdAbility : public UBaseAbility
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = AbilityStats, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float lifetime;

	UPROPERTY(Category = AbilityStats, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float radius;

	UPROPERTY(Category = AbilityStats, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float period;

	bool isFlagExist;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	USN4K3ThirdAbility();

	void removeAbilityEffect(class ABaseCharacter* target);
	
	void setIsFlagExist(bool isFlagExist);

	bool getIsFlagExist() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	~USN4K3ThirdAbility() = default;
};
