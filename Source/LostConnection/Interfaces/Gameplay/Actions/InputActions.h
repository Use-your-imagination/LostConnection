// Copyright (c) 2021 Use-your-imagination

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "InputActions.generated.h"

UINTERFACE(MinimalAPI)
class UInputActions : public UInterface
{
	GENERATED_BODY()
};

class LOSTCONNECTION_API IInputActions
{
	GENERATED_BODY()

	
public:
	IInputActions() = default;

	UFUNCTION(BlueprintNativeEvent)
	void pressZoomAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseZoomAction();

	UFUNCTION(BlueprintNativeEvent)
	void pressWeaponSelectorAction();

	UFUNCTION(BlueprintNativeEvent)
	void releaseWeaponSelectorAction();
};
