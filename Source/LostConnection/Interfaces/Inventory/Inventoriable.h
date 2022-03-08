// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Inventoriable.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UInventoriable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IInventoriable
{
	GENERATED_BODY()

public:
	IInventoriable() = default;

	UFUNCTION(Category = Inventory, BlueprintCallable)
	virtual const FText& getItemName() const = 0;

	UFUNCTION(Category = Inventory, BlueprintCallable)
	virtual const FText& getItemDescription() const = 0;
};