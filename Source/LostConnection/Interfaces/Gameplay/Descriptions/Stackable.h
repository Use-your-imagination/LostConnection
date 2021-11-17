// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Stackable.generated.h"

UINTERFACE(BlueprintType)
class UStackable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IStackable
{
	GENERATED_BODY()

protected:
	virtual float calculateStacks(float damage) const;

	virtual bool increaseStacksCondition(float damage) const;

	virtual bool decreaseStacksCondition(float damage) const;

public:
	IStackable() = default;

	virtual void increaseStacks(float damage);

	virtual void decreaseStacks(float damage);

	virtual float getDamageToStacksCoefficient() const = 0;

	virtual float& getStacks() = 0;

	virtual float getStacks() const = 0;
};
