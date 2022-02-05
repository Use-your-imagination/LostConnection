// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "EnergyShields/BaseEnergyShield.h"

#include "LightEnergyShield.generated.h"

UCLASS()
class LOSTCONNECTION_API ULightEnergyShield : public UBaseEnergyShield
{
	GENERATED_BODY()
	
public:
	ULightEnergyShield() = default;

	virtual ~ULightEnergyShield() = default;
};
