// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Modules/BaseWeaponModule.h"

#include "WeaponModulesHolder.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UWeaponModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponModulesHolder
{
	GENERATED_BODY()

public:
	IWeaponModulesHolder() = default;

	virtual void addWeaponModule(UBaseWeaponModule* module) = 0;

	virtual TArray<UBaseWeaponModule*> getWeaponModules() const = 0;
};
