// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "EnergyShields/BaseEnergyShield.h"

#include "HeavyEnergyShield.generated.h"

UCLASS()
class LOSTCONNECTION_API UHeavyEnergyShield : public UBaseEnergyShield
{
	GENERATED_BODY()
	
public:
	UHeavyEnergyShield() = default;

	virtual ~UHeavyEnergyShield() = default;
};
