// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Modules/Module.h"

#include "MainModule.generated.h"

UINTERFACE(MinimalAPI)
class UMainModule : public UModule
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IMainModule : public IModule
{
	GENERATED_BODY()

public:
	IMainModule() = default;
};
