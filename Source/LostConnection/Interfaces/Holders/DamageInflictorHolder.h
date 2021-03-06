// Copyright (c) 2022 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Holders/Utility/DamageInflictorUtility.h"

#include "DamageInflictorHolder.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UDamageInflictorHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IDamageInflictorHolder
{
	GENERATED_BODY()

public:
	IDamageInflictorHolder() = default;

	UFUNCTION(Category = "Utility|DamageInflictor", BlueprintCallable)
	virtual UDamageInflictorUtility* getDamageInflictorUtility() const = 0;
};
