// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "DamageInflictor.generated.h"

UINTERFACE(BlueprintType)
class UDamageInflictor : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageInflictor
{
	GENERATED_BODY()

public:
	IDamageInflictor() = default;

	virtual float calculateTotalDamage() const;

	virtual void appendIncreaseDamageCoefficient(float coefficient) = 0;

	virtual void removeIncreaseDamageCoefficient(float coefficient) = 0;

	virtual void appendMoreDamageCoefficient(float coefficient) = 0;

	virtual void removeMoreDamageCoefficient(float coefficient) = 0;

	virtual void setBaseDamage(float damage) = 0;

	virtual void setAddedDamage(float addedDamage) = 0;

	virtual void setAdditionalDamage(float additionalDamage) = 0;

	virtual float getBaseDamage() const = 0;

	virtual float getAddedDamage() const = 0;

	virtual float getAdditionalDamage() const = 0;

	virtual const TArray<float>& getIncreaseDamageCoefficients() const = 0;

	virtual const TArray<float>& getMoreDamageCoefficients() const = 0;

	virtual TObjectPtr<AController> getDamageInstigator() const = 0;
};
