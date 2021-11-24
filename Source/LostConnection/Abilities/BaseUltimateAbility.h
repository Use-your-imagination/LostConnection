// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseAbility.h"

#include "BaseUltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseUltimateAbility : public UBaseAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = AbilityState, EditDefaultsOnly, Replicated, BlueprintReadOnly)
	float cooldown;

	UPROPERTY(Category = AbilityState, Replicated, BlueprintReadOnly)
	float currentCooldown;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UBaseUltimateAbility();

	virtual float getCooldown() const final;

	virtual float getCurrentCooldown() const final;

	virtual void applyAbility(class ABaseCharacter* target) override;

	virtual void useAbility() override;

	virtual void Tick(float DeltaTime) override;

	virtual ~UBaseUltimateAbility() = default;
};
