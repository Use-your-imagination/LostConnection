// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "EnergyShields/BaseEnergyShield.h"

#include "EmptyEnergyShield.generated.h"

UCLASS()
class LOSTCONNECTION_API UEmptyEnergyShield : public UBaseEnergyShield
{
	GENERATED_BODY()
	
public:
	UEmptyEnergyShield() = default;

	virtual ~UEmptyEnergyShield() = default;
};
