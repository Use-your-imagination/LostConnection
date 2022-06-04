// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "BaseLootFunction.h"
#include "Utility/Enums.h"

#include "BaseModulesLootFunction.generated.h"

UCLASS()
class LOSTCONNECTION_API UBaseModulesLootFunction : public UBaseLootFunction
{
	GENERATED_BODY()

public:
	UBaseModulesLootFunction() = default;

	UFUNCTION(Category = "Rarity", BlueprintNativeEvent)
	EModuleQuality getModuleQuality() const;

	virtual ~UBaseModulesLootFunction() = default;
};
