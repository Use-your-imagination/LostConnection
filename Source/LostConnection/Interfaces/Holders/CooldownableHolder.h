// Copyright (c) 2022 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Utility/CooldownableUtility.h"

#include "CooldownableHolder.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UCooldownableHolder : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API ICooldownableHolder
{
	GENERATED_BODY()

public:
	ICooldownableHolder() = default;

	UFUNCTION(Category = "Utility|Cooldownable", BlueprintCallable)
	virtual UCooldownableUtility* getCooldownableUtility() const = 0;
};
