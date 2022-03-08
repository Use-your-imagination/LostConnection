// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseModule.h"

#include "BaseWeaponModule.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseWeaponModule : public UBaseModule
{
	GENERATED_BODY()
	
public:
	UBaseWeaponModule() = default;

	virtual ~UBaseWeaponModule() = default;
};
