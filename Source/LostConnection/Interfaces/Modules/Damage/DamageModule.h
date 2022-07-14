// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/Gameplay/Descriptions/DamageAffecter.h"
#include "Interfaces/Gameplay/Statuses/Ailment.h"

#include "DamageModule.generated.h"

UINTERFACE(BlueprintType)
class UDamageModule : public UDamageAffecter
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageModule : public IDamageAffecter
{
	GENERATED_BODY()

public:
	IDamageModule() = default;

	virtual ETypeOfDamage getDamageType() const;
};
