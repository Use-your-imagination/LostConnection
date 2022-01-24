// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseUltimateAbility.h"

#include "SN4K3UltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API USN4K3UltimateAbility : public UBaseUltimateAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = SN4K3, EditDefaultsOnly, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float abilityDuration;

	UPROPERTY(Category = SN4K3, EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UAnimMontage* returnAnimation;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	bool isUltimateAbilityUsed;

	UPROPERTY(Category = SN4K3, Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float currentAbilityDuration;

	UPROPERTY(Category = SN4K3, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FVector ultimatePlaceholderLocation;

	TWeakObjectPtr<class ASN4K3UltimateAbilityPlaceholder> ultimatePlaceholder;

private:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void setCollisionResponseToPawnChannel(class ABaseCharacter* target, ECollisionResponse response);

public:
	USN4K3UltimateAbility();

	bool getIsUltimateAbilityUsed() const;

	UAnimMontage* getReturnAnimation() const;

	float getAbilityDuration() const;

	float getCurrentAbilityDuration() const;

	const TWeakObjectPtr<class ASN4K3UltimateAbilityPlaceholder>& getUltimatePlaceholder() const;

	void applyAbility(class ABaseCharacter* target) override;

	void useAbility() override;

	void Tick(float DeltaTime) override;

	~USN4K3UltimateAbility() = default;
};

inline bool USN4K3UltimateAbility::getIsUltimateAbilityUsed() const
{
	return isUltimateAbilityUsed;
}
