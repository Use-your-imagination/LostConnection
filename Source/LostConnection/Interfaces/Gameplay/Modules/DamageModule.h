// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "DamageModule.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageModule : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageModule
{
	GENERATED_BODY()

public:
	IDamageModule() = default;
};
