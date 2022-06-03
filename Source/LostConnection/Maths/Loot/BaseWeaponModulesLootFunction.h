// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseLootFunction.h"
#include "Utility/Enums.h"

#include "BaseWeaponModulesLootFunction.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseWeaponModulesLootFunction : public UBaseLootFunction
{
	GENERATED_BODY()
	
public:
	UBaseWeaponModulesLootFunction() = default;

	UFUNCTION(Category = "Rarity", BlueprintNativeEvent)
	EModuleQuality getModuleQuality() const;

	virtual ~UBaseWeaponModulesLootFunction() = default;
};
