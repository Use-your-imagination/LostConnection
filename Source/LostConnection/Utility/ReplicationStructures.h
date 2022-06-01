// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "Abilities/BaseAbility.h"
#include "Weapons/BaseWeapon.h"

#include "ReplicationStructures.generated.h"

UENUM()
enum class EReplicationStructures
{
	NONE
};

USTRUCT(BlueprintType)
struct LOSTCONNECTION_API FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Data, BlueprintReadOnly)
	int32 ammoCount;

	UPROPERTY(Category = Data, BlueprintReadOnly)
	EAmmoType ammoType;

	FAmmoData(EAmmoType ammoType = EAmmoType::small, int32 ammoCount = 0);
};

USTRUCT()
struct FCooldownableData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float remainingCooldown;

public:
	FCooldownableData(float remainingCooldown = 0.0f);
};

USTRUCT()
struct FCooldownableAbilitiesData : public FCooldownableData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EAbilitySlot slot;

public:
	FCooldownableAbilitiesData(EAbilitySlot slot = EAbilitySlot::empty, float remainingCooldown = 0.0f);
};

USTRUCT()
struct FCooldownableWeaponsData : public FCooldownableData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EWeaponSlotType slot;

public:
	FCooldownableWeaponsData(EWeaponSlotType slot = EWeaponSlotType::none, float remainingCooldown = 0.0f);
};
