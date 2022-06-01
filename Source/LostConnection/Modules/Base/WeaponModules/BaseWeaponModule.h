// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Modules/Base/BaseModule.h"

#include "BaseWeaponModule.generated.h"

UCLASS(Abstract)
class LOSTCONNECTION_API UBaseWeaponModule : public UBaseModule
{
	GENERATED_BODY()
	
public:
	UBaseWeaponModule() = default;

	virtual ~UBaseWeaponModule() = default;
};
