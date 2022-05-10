// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "EnergyShields/BaseEnergyShield.h"

#include "NormalEnergyShield.generated.h"

UCLASS()
class LOSTCONNECTION_API UNormalEnergyShield : public UBaseEnergyShield
{
	GENERATED_BODY()
	
public:
	UNormalEnergyShield() = default;

	virtual ~UNormalEnergyShield() = default;
};
