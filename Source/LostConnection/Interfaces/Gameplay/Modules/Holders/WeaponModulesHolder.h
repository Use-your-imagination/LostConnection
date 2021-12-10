// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "WeaponModulesHolder.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponModulesHolder
{
	GENERATED_BODY()

public:
	IWeaponModulesHolder() = default;

	/// @brief 
	/// @return Array of IMainModule
	virtual const TArray<UObject*>& getWeaponModules() const = 0;
};
