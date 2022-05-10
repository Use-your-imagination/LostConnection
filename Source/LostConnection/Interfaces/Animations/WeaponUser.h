// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Weapons/BaseWeapon.h"

#include "WeaponUser.generated.h"

UINTERFACE(BlueprintType)
class UWeaponUser : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IWeaponUser
{
	GENERATED_BODY()

public:
	IWeaponUser() = default;

	UFUNCTION(Category = Weapon, BlueprintNativeEvent, BlueprintCallable)
	void weaponUpdate(UBaseWeapon* weapon);
};
