// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "DamageModule.h"

#include "WeaponDamageModule.generated.h"

UINTERFACE()
class UWeaponDamageModule : public UDamageModule
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponDamageModule : public IDamageModule
{
	GENERATED_BODY()

public:
	IWeaponDamageModule() = default;
};
