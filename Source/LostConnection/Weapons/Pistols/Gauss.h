// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Weapons/BaseWeapon.h"

#include "Gauss.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API AGauss : public ABaseWeapon
{
	GENERATED_BODY()

public:
	AGauss();

	~AGauss() = default;
};
