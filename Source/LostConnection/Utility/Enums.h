// Copyright (c) 2022 Use Your Imagination

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
enum class EModuleQuality : uint8
{
	broken UMETA(DisplayName = "Broken"),
	bronze UMETA(DisplayName = "Bronze"),
	silver UMETA(DisplayName = "Silver"),
	gold UMETA(DisplayName = "Gold"),
	platinum UMETA(DisplayName = "Platinum")
};

UENUM(BlueprintType)
enum class EAbilitySlot : uint8
{
	empty UMETA(DisplayName = "No ability"),
	passiveAbility UMETA(DisplayName = "Passive ability"),
	firstAbility UMETA(DisplayName = "First ability"),
	secondAbility UMETA(DisplayName = "Second ability"),
	thirdAbility UMETA(DisplayName = "Third ability"),
	ultimateAbility UMETA(DisplayName = "Ultimate ability")
};

UENUM(BlueprintType)
enum class ETypeOfDamage : uint8
{
	any UMETA(DisplayName = "Any"),
	physical UMETA(DisplayName = "Physical"),
	nanite UMETA(DisplayName = "Nanite"),
	fire UMETA(DisplayName = "Fire"),
	electricity UMETA(DisplayName = "Electricity"),
	radiation UMETA(DisplayName = "Radiation"),
	cold UMETA(DisplayName = "Cold")
};

UENUM(BlueprintType)
enum class EExecutionOutputs : uint8
{
	Success UMETA(DisplayName = "Success"),
	Fail UMETA(DisplayName = "Fail")
};
