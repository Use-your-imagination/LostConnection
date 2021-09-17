// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Weapons/BaseWeapon.h"

#include "Hipter.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API UHipter : public UBaseWeapon
{
	GENERATED_BODY()
	
public:
	UHipter();

	virtual void alternativeMode() final override;

	~UHipter() = default;
};
