// Copyright (c) 2021 Use Your Imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "AITargeted.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UAITargeted : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IAITargeted
{
	GENERATED_BODY()

public:
	IAITargeted() = default;

	UFUNCTION(BlueprintCallable)
	virtual bool getIsAlly() const = 0;
};
