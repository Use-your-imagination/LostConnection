// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Base/DamageInflictor.h"

#include "DamageAffecter.generated.h"

UINTERFACE(MinimalAPI)
class UDamageAffecter : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageAffecter
{
	GENERATED_BODY()

public:
	IDamageAffecter() = default;

	virtual void affect(FDamageStructure& damage) = 0;
};
