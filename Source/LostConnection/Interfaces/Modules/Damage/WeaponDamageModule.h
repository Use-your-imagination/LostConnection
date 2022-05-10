// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "WeaponDamageModule.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponDamageModule : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponDamageModule
{
	GENERATED_BODY()

public:
	IWeaponDamageModule() = default;

	virtual float getAddedDamage() const = 0;

	virtual float getIncreasedDamage() const = 0;

	virtual float getMoreDamage() const = 0;

	virtual float getAdditionalDamage() const = 0;
	
	virtual ETypeOfDamage getDamageType() const;
};
