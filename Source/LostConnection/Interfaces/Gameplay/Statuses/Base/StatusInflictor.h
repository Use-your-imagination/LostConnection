// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Descriptions/Base/DamageInflictor.h"

#include "StatusInflictor.generated.h"

UINTERFACE(BlueprintType)
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
