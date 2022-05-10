// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Utility/Enums.h"

#include "Ailment.generated.h"

UINTERFACE(MinimalAPI)
class UAilment : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilment
{
	GENERATED_BODY()

public:
	IAilment() = default;

	virtual ETypeOfDamage getAilmentDamageType() const = 0;
};
