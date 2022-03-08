// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Abilities/BaseAbility.h"
#include "Weapons/BaseWeapon.h"

#include "ReplicationStructures.generated.h"

UCLASS()
class LOSTCONNECTION_API UReplicationStructures : public UObject
{
	GENERATED_BODY()

public:
	UReplicationStructures() = default;

	~UReplicationStructures() = default;
};

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Data, BlueprintReadOnly)
	int32 ammoCount;

	UPROPERTY(Category = Data, BlueprintReadOnly)
	ammoTypes ammoType;

	FAmmoData(ammoTypes ammoType = ammoTypes::small, int32 ammoCount = 0);
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
	abilitySlot slot;

public:
	FCooldownableAbilitiesData(abilitySlot slot = abilitySlot::empty, float remainingCooldown = 0.0f);
};

USTRUCT()
struct FCooldownableWeaponsData : public FCooldownableData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	weaponSlotTypes slot;

public:
	FCooldownableWeaponsData(weaponSlotTypes slot = weaponSlotTypes::none, float remainingCooldown = 0.0f);
};
