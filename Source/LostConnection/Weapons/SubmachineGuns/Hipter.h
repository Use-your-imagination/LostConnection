// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseEntities/BaseWeapon.h"

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

	~UHipter() = default;
};
