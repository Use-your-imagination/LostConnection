// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Module.generated.h"

UINTERFACE(MinimalAPI)
class UModule : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IModule
{
	GENERATED_BODY()

public:
	IModule() = default;


};
