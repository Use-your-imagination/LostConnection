// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "MainModule.h"

#include "DamageModule.generated.h"

UINTERFACE(MinimalAPI)
class UDamageModule : public UMainModule
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageModule : public IMainModule
{
	GENERATED_BODY()

public:
	IDamageModule() = default;

	virtual float getAddedDamage() const = 0;

	virtual float getIncreasedDamage() const = 0;

	virtual float getMoreDamage() const = 0;

	virtual float getAdditionalDamage() const = 0;
};
