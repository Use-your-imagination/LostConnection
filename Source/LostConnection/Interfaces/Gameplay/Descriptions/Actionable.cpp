// Copyright (c) 2021 Use-your-imagination

#include "Actionable.h"

#include "GameFramework/InputSettings.h"

#include "Characters/BaseDrone.h"

FString IActionable::getActionMessage() const
{
	TArray<FInputActionKeyMapping> actionKey;
	GetDefault<UInputSettings>()->GetActionMappingByName("Action", actionKey);

	return FText::FormatNamed(FText::FromStringTable("/Game/Text/Actions.Actions", "DefaultActionMessage"), TEXT("ActionHotkey"), actionKey[0].Key.GetDisplayName()).ToString();
}
