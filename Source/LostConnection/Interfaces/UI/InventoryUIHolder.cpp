// Copyright (c) 2022 Use Your Imagination

#include "InventoryUIHolder.h"

#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"
#include "Engine/LostConnectionPlayerState.h"
#include "Constants/Constants.h"

void IInventoryUIHolder::showInventory_Implementation(APlayerController* playerController)
{
	UInventoryWidget* widget = IInventoryUIHolder::Execute_getInventoryWidget(this->_getUObject());

	playerController->GetPlayerState<ALostConnectionPlayerState>()->getCurrentUI()->SetVisibility(ESlateVisibility::Hidden);

	widget->onShow();

	playerController->SetInputMode(FInputModeGameAndUI());

	UUtilityBlueprintFunctionLibrary::showMouseCursor(playerController, true);
}

void IInventoryUIHolder::hideInventory_Implementation(APlayerController* playerController)
{
	UInventoryWidget* widget = IInventoryUIHolder::Execute_getInventoryWidget(this->_getUObject());

	playerController->SetInputMode(FInputModeGameOnly());

	UUtilityBlueprintFunctionLibrary::showMouseCursor(playerController, false);

	widget->onHide();
}
