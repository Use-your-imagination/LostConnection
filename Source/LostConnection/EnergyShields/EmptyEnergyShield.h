// Copyright (c) 2022 Use Your Imagination

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

	~UEmptyEnergyShield() = default;
};
