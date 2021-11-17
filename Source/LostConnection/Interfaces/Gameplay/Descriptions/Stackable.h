// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Stackable.generated.h"

UINTERFACE(MinimalAPI)
class UStackable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IStackable
{
	GENERATED_BODY()

public:
	IStackable() = default;

	virtual void setStacks(float damage) = 0;

	virtual float getStacks() const = 0;
};
