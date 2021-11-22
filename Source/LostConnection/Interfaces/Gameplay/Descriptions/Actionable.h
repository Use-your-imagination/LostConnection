// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Actionable.generated.h"

UINTERFACE(BlueprintType, Meta = (CannotImplementInterfaceInBlueprint))
class UActionable : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IActionable
{
	GENERATED_BODY()

public:
	IActionable() = default;

	UFUNCTION()
	virtual void action(class ABaseDrone* player) = 0;

	UFUNCTION(BlueprintCallable)
	virtual FString getActionMessage() const;
};
