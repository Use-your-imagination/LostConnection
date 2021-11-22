// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "MovementActions.generated.h"

UINTERFACE(MinimalAPI)
class UMovementActions : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IMovementActions
{
	GENERATED_BODY()

public:
	IMovementActions() = default;

	UFUNCTION(BlueprintNativeEvent)
	void pressCrouchAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseCrouchAction();

	UFUNCTION(BlueprintNativeEvent)
	void pressJumpAction();
};
