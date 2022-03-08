// Copyright (c) 2022 Use-your-imagination

#include "InventoryUIHolder.h"

#include "Utility/Blueprints/UtilityBlueprintFunctionLibrary.h"
#include "Engine/LostConnectionPlayerState.h"

void IInventoryUIHolder::showInventory_Implementation(APlayerController* playerController)
{
	playerController->GetPlayerState<ALostConnectionPlayerState>()->getCurrentUI()->SetVisibility(ESlateVisibility::Hidden);

	IInventoryUIHolder::Execute_getInventoryWidget(this->_getUObject())->AddToViewport(TNumericLimits<int32>::Max());

	playerController->SetInputMode(FInputModeGameAndUI());

	UUtilityBlueprintFunctionLibrary::showMouseCursor(playerController, true);
}

void IInventoryUIHolder::hideInventory_Implementation(APlayerController* playerController)
{
	playerController->SetInputMode(FInputModeGameOnly());

	UUtilityBlueprintFunctionLibrary::showMouseCursor(playerController, false);

	IInventoryUIHolder::Execute_getInventoryWidget(this->_getUObject())->RemoveFromViewport();

	playerController->GetPlayerState<ALostConnectionPlayerState>()->getCurrentUI()->SetVisibility(ESlateVisibility::Visible);
}
