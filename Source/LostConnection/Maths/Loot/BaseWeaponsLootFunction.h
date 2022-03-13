// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseLootFunction.h"
#include "Utility/Enums.h"

#include "BaseWeaponsLootFunction.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseWeaponsLootFunction : public UBaseLootFunction
{
	GENERATED_BODY()
	
public:
	UBaseWeaponsLootFunction() = default;

	UFUNCTION(Category = "Rarity", BlueprintNativeEvent)
	EWeaponRarity getWeaponRarity() const;

	virtual ~UBaseWeaponsLootFunction() = default;
};
