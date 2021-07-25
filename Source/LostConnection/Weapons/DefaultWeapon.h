// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseEntities/BaseWeapon.h"

#include "DefaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API UDefaultWeapon : public UBaseWeapon
{
	GENERATED_BODY()

public:
	UDefaultWeapon();

	~UDefaultWeapon() = default;
};
