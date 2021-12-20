// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseAbility.h"
#include "Interfaces/Gameplay/Descriptions/Cooldownable.h"

#include "BaseUltimateAbility.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseUltimateAbility : 
	public UBaseAbility,
	public ICooldownable
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

	virtual void applyAbility(class ABaseCharacter* target) override;

	virtual void useAbility() override;

	virtual float getCooldown() const final override;

	virtual float& getCurrentCooldown() final override;

	virtual ~UBaseUltimateAbility() = default;
};
