// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseAbility.h"

#include "BaseUltimateAbility.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ABaseUltimateAbility : public ABaseAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Replicated)
	float cooldown;

	UPROPERTY(Replicated)
	float currentCooldown;

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	ABaseUltimateAbility();

	virtual void applyAbility(class ABaseCharacter* target) override;

	virtual void useAbility() override;

	virtual ~ABaseUltimateAbility() = default;
};
