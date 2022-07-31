// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Buff.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UBuff : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IBuff
{
	GENERATED_BODY()

public:
	IBuff() = default;
};
