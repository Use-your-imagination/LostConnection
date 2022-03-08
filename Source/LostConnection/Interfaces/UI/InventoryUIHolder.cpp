// Copyright (c) 2022 Use-your-imagination

#include "InventoryUIHolder.h"

#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"
#include "Engine/LostConnectionPlayerState.h"

void IInventoryUIHolder::showInventory_Implementation(APlayerController* playerController)
{
	UInventoryWidget* widget = IInventoryUIHolder::Execute_getInventoryWidget(this->_getUObject());

	playerController->GetPlayerState<ALostConnectionPlayerState>()->getCurrentUI()->SetVisibility(ESlateVisibility::Hidden);

	widget->AddToViewport(TNumericLimits<int32>::Max());

	widget->onShow();

	playerController->SetInputMode(FInputModeGameAndUI());

	UUtilityBlueprintFunctionLibrary::showMouseCursor(playerController, true);
}

void IInventoryUIHolder::hideInventory_Implementation(APlayerController* playerController)
{
	UInventoryWidget* widget = IInventoryUIHolder::Execute_getInventoryWidget(this->_getUObject());

	playerController->SetInputMode(FInputModeGameOnly());

	UUtilityBlueprintFunctionLibrary::showMouseCursor(playerController, false);

	widget->RemoveFromViewport();

	widget->onHide();

	playerController->GetPlayerState<ALostConnectionPlayerState>()->getCurrentUI()->SetVisibility(ESlateVisibility::Visible);
}
