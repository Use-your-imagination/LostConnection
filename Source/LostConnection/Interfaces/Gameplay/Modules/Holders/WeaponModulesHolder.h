// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Modules/WeaponModules/WeaponModule.h"
#include "Network/NetworkObject.h"

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

	virtual void addWeaponModule(IWeaponModule* module) = 0;

	/// @brief 
	/// @return Array of IMainModule
	virtual const TArray<UNetworkObject*>& getWeaponModules() const = 0;
};
