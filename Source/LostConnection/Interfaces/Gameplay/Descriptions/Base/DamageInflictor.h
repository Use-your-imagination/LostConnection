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

	virtual void increaseAdditionalInflictorDamage(float amount);

	virtual void decreaseAdditionalInflictorDamage(float amount);

	virtual void setInflictorDamage(float damage) = 0;

	virtual void setAdditionalInflictorDamage(float additionalDamage) = 0;

	virtual float getInflictorDamage() const = 0;

	virtual float getAdditionalInflictorDamage() const = 0;
};
