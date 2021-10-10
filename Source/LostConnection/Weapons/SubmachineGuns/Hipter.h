// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Weapons/BaseWeapon.h"

#include "Hipter.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API AHipter : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	AHipter();

	virtual void alternativeMode() final override;

	~AHipter() = default;
};
