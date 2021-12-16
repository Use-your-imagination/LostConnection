// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "StatusInflictor.generated.h"

UINTERFACE(MinimalAPI)
class UStatusInflictor : public UDamageInflictor
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IStatusInflictor : public IDamageInflictor
{
	GENERATED_BODY()

public:
	IStatusInflictor() = default;
};