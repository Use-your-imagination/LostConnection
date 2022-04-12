// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "AmmoDropable.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UAmmoDropable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAmmoDropable
{
	GENERATED_BODY()

public:
	IAmmoDropable() = default;

	virtual float getSmallAmmoDropChance() const = 0;
	
	virtual float getLargeAmmoDropChance() const = 0;

	virtual float getEnergyAmmoDropChance() const = 0;

	virtual FTransform getCurrentPosition();
};
