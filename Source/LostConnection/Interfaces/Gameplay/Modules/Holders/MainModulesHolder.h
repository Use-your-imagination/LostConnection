// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "MainModulesHolder.generated.h"

UINTERFACE(MinimalAPI)
class UMainModulesHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IMainModulesHolder
{
	GENERATED_BODY()

public:
	IMainModulesHolder() = default;

	/// @brief 
	/// @return Array of IMainModule
	virtual const TArray<UObject*>& getMainModules() const = 0;
};
