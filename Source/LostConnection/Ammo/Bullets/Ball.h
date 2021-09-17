// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Ammo/BaseAmmo.h"

#include "Ball.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ABall : public ABaseAmmo
{
	GENERATED_BODY()
	
private:
	GET_STATIC_CLASS_OVERRIDE(ABall)

public:
	ABall();

	~ABall() = default;
};
