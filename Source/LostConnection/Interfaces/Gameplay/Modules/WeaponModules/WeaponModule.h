// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Modules/Module.h"

#include "WeaponModule.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponModule : public UModule
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponModule : public IModule
{
	GENERATED_BODY()

public:
	IWeaponModule() = default;
};
