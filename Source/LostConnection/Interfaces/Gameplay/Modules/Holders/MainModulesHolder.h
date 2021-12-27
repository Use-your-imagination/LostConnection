// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Interfaces/Gameplay/Modules/MainModules/MainModule.h"
#include "Network/NetworkObject.h"

#include "MainModulesHolder.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UMainModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IMainModulesHolder
{
	GENERATED_BODY()

public:
	IMainModulesHolder() = default;

	virtual void addMainModule(IMainModule* module) = 0;

	/// @brief 
	/// @return Array of IMainModule
	virtual const TArray<UNetworkObject*>& getMainModules() const = 0;
};
