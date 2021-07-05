// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseEntities/BaseAmmo.h"

#include "DefaultAmmo.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ADefaultAmmo : public ABaseAmmo
{
	GENERATED_BODY()
	
private:
	GET_STATIC_CLASS_OVERRIDE(ADefaultAmmo)

public:
	ADefaultAmmo();

	~ADefaultAmmo() = default;
};
