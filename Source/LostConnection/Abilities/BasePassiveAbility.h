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
	
protected:
	virtual void useAbility(AActor* target);

public:
	ABasePassiveAbility() = default;

	virtual ~ABasePassiveAbility() = default;
};
