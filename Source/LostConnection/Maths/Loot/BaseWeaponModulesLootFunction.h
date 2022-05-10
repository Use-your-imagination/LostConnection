// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseLootFunction.h"

#include "BaseWeaponModulesLootFunction.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseWeaponModulesLootFunction : public UBaseLootFunction
{
	GENERATED_BODY()
	
public:
	UBaseWeaponModulesLootFunction() = default;

	virtual ~UBaseWeaponModulesLootFunction() = default;
};
