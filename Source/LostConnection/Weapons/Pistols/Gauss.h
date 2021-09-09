// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseEntities/BaseWeapon.h"

#include "Gauss.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API UGauss : public UBaseWeapon
{
	GENERATED_BODY()

public:
	UGauss();

	~UGauss() = default;
};
