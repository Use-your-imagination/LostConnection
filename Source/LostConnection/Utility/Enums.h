// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
#include "HAL/Platform.h"

#include "Enums.generated.h"

UENUM()
enum class EEnum
{
	NONE
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	automatic UMETA(DisplayName = "Automatic"),
	semiAutomatic UMETA(DisplayName = "Semi-automatic"),
	single UMETA(DisplayName = "Single"),
	delay UMETA(DisplayName = "Delay")
};

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	small UMETA(DisplayName = "Small ammo"),
	large UMETA(DisplayName = "Large ammo"),
	energy UMETA(DisplayName = "Energy ammo"),
	defaultType UMETA(DisplayName = "Default ammo")
};

UENUM(BlueprintType)
enum class EWeaponSlotType : uint8
{
	none UMETA(DisplayName = "None"),
	primaryWeaponSlot UMETA(DisplayName = "Primary weapon slot"),
	secondaryWeaponSlot UMETA(DisplayName = "Secondary weapon slot"),
	defaultWeaponSlot UMETA(DisplayName = "Default weapon slot"),
	firstInactiveWeaponSlot UMETA(DisplayName = "First inactive weapon slot"),
	secondInactiveWeaponSlot UMETA(DisplayName = "Second inactive weapon slot")
};

UENUM(BlueprintType)
enum class EWeaponRarity : uint8
{
	normal UMETA(DisplayName = "Normal"),
	rare UMETA(DisplayName = "Rare"),
	epic UMETA(DisplayName = "Epic"),
	legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EAbilitySlot : uint8
{
	empty = 0 UMETA(DisplayName = "No ability"),
	passiveAbility = 1 UMETA(DisplayName = "Passive ability"),
	firstAbility = 2 UMETA(DisplayName = "First ability"),
	secondAbility = 3 UMETA(DisplayName = "Second ability"),
	thirdAbility = 4 UMETA(DisplayName = "Third ability"),
	ultimateAbility = 5 UMETA(DisplayName = "Ultimate ability")
};

UENUM(BlueprintType)
enum class ETypeOfDamage : uint8
{
	none = 0 UMETA(DisplayName = "None"),
	physical = 1 UMETA(DisplayName = "Physical"),
	nanite = 2 UMETA(DisplayName = "Nanite"),
	fire = 3 UMETA(DisplayName = "Fire"),
	electricity = 4 UMETA(DisplayName = "Electricity"),
	radiation = 5 UMETA(DisplayName = "Radiation"),
	cold = 6 UMETA(DisplayName = "Cold")
};

UENUM(BlueprintType)
enum class EExecutionOutputs : uint8
{
	Success UMETA(DisplayName = "Success"),
	Fail UMETA(DisplayName = "Fail")
};
