// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../BaseEntities/BaseWeapon.h"

#include "DefaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ADefaultWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ADefaultWeapon();

	~ADefaultWeapon() = default;
};
