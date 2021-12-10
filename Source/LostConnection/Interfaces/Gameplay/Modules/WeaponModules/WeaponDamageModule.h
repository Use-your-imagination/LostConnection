// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "WeaponModule.h"

#include "WeaponDamageModule.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponDamageModule : public UWeaponModule
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponDamageModule : public IWeaponModule
{
	GENERATED_BODY()

public:
	IWeaponDamageModule() = default;
};
