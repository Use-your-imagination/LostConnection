// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "DamageModule.generated.h"

UINTERFACE(BlueprintType)
class UDamageModule : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageModule
{
	GENERATED_BODY()

public:
	IDamageModule() = default;

	virtual float getAddedDamage() const = 0;

	virtual float getIncreaseDamageCoefficient() const = 0;

	virtual float getMoreDamageCoefficient() const = 0;

	virtual float getAdditionalDamage() const = 0;

	virtual ETypeOfDamage getDamageType() const;
};
