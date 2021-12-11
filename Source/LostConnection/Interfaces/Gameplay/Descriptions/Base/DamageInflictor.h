// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "DamageInflictor.generated.h"

UINTERFACE(MinimalAPI)
class UDamageInflictor : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageInflictor
{
	GENERATED_BODY()

public:
	IDamageInflictor() = default;

	virtual void increaseBaseDamage(float amount);

	virtual void decreaseBaseDamage(float amount);

	virtual void setBaseDamage(float damage) = 0;

	virtual float calculateTotalDamage() const;

	virtual float getBaseDamage() const = 0;

	virtual float getAddedDamage() const = 0;

	virtual TArray<float> getIncreasedDamageCoefficients() const = 0;

	virtual TArray<float> getMoreDamageCoefficients() const = 0;

	virtual float getAdditionalDamage() const = 0;
};
