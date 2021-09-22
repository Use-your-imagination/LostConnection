// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"

#include "BasePassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ABasePassiveAbility : public ABaseAbility
{
	GENERATED_BODY()

public:
	ABasePassiveAbility() = default;

	virtual void applyAbility(class ABaseDrone* target) override;

	virtual void useAbility() override;

	virtual ~ABasePassiveAbility() = default;
};
