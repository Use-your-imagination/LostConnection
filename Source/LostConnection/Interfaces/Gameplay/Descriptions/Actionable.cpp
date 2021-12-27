// Copyright (c) 2021 Use-your-imagination

#include "Actionable.h"

#include "GameFramework/InputSettings.h"

#include "Characters/BaseDrone.h"
#include "Constants/Constants.h"

FText IActionable::getActionMessage() const
{
	TArray<FInputActionKeyMapping> actionKey;
	GetDefault<UInputSettings>()->GetActionMappingByName("Action", actionKey);

	return FText::FormatNamed(FText::FromStringTable(UConstants::actionStringTablePath, UConstants::defaultActionMessageKey), UConstants::actionHotkey, actionKey[0].Key.GetDisplayName());
}
