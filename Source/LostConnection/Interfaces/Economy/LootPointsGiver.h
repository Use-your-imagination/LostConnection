// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "LootPointsGiver.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class ULootPointsGiver : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ILootPointsGiver
{
	GENERATED_BODY()

public:
	ILootPointsGiver() = default;

	UFUNCTION(Category = Economy, BlueprintCallable)
	virtual int32 getLootPoints() const = 0;
};
