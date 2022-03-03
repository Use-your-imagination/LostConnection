// Copyright (c) 2021 Use-your-imagination

#include "Actionable.h"

#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"
#include "Characters/BaseDrone.h"
#include "Constants/Constants.h"

FText IActionable::getActionMessage() const
{
	TArray<FInputActionKeyMapping> actionKey = UUtilityBlueprintFunctionLibrary::getActionMapping("Action");

	return FText::FormatNamed(FText::FromStringTable(UConstants::actionStringTablePath, UConstants::defaultActionMessageKey), UConstants::actionHotkey, actionKey[0].Key.GetDisplayName());
}
