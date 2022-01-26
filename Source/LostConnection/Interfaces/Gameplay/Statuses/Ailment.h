// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Ailment.generated.h"

UENUM(BlueprintType)
enum class typeOfDamage : uint8
{
	none = 0 UMETA(DisplayName = "None"),
	physical = 1 UMETA(DisplayName = "Physical"),
	nanite = 2 UMETA(DisplayName = "Nanite"),
	fire = 3 UMETA(DisplayName = "Fire"),
	electricity = 4 UMETA(DisplayName = "Electricity"),
	radiation = 5 UMETA(DisplayName = "Radiation"),
	cold = 6 UMETA(DisplayName = "Cold")
};

UINTERFACE(MinimalAPI)
class UAilment : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAilment
{
	GENERATED_BODY()

public:
	IAilment() = default;

	virtual typeOfDamage getAilmentDamageType() const = 0;
};
