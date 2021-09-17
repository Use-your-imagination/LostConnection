// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Ammo/BaseAmmo.h"

#include "Bullet.generated.h"

/**
 * 
 */
UCLASS()
class LOSTCONNECTION_API ABullet : public ABaseAmmo
{
	GENERATED_BODY()

private:
	GET_STATIC_CLASS_OVERRIDE(ABullet)

public:
	ABullet();

	~ABullet() = default;
};
